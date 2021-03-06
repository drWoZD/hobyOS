.code32
.text
    .global loader                 

    .set FLAGS,    0x04            # Флаги для ядра
    .set MAGIC,    0x1BADB002        # 'Магічне' число для multiboot (в multiboot інше)
    .set CHECKSUM, -(MAGIC + FLAGS)  # Контрольна сума

    .align 4    # Обовязково треба вирівняти до int
    .long  MAGIC 
    .long  FLAGS
    .long  CHECKSUM
    .space 20, 0
    .long  0x01
    .long  0x50
    .long  0x19
    .long  0x0

    # Власне код який почне виконувати завантажувач
    
loader:
    movl  $(stack + 0x4000), %esp # Ініціалізація стеку
    movl  %eax, magic                # Збереження магічного числа. Можна опустити 
    movl  %ebx, mbd                  # Збереження структури з параметрами які пеердав завантажувач

    # Тут я вирішив ініціалізувати сторінкову адресацію
    
    movl  $page_table, %edi  
    movl  $0x87, %eax       # Перший запис в каталозі таблиць вказує на 4Мб столрінку
    stosl
    
    lea   0x1003(%edi), %eax  # Всі таблиці йдути зразу після каталогу
    movl  $1023, %ecx         # # Заповнюю весь каталог
    
table_dir_loop:
    stosl 
    addl $0x1000, %eax
    loop table_dir_loop
    
    # Зараз буде заповнення таблиць
    
    movl  $0x00400007, %eax  # Перша сторінка в першій таблиці починається з 4Мб 
    movl  $1048576, %ecx     # Заповнюємо всі 1024 таблиці в кожній 1024 сторінки, тобто описуємо 4Гб

table_loop:
    stosl
    addl  $0x00001000, %eax
    loop  table_loop
    
    # Дозволяємо використання великих сторінок (В даному випадку 4Мб)
    movl  %cr4, %eax
    orl   $0x10, %eax
    movl  %eax, %cr4
    
    # Записуємо адресу каталогу таблиць в cr3
    movl  $page_table, %eax
    movl  %eax, %cr3
    
    # Вмикаємо сторінкову адресацію
    movl  %cr0, %eax
    orl   $0x80000000, %eax
    movl  %eax, %cr0
    
    # Викликаємо Сішну функцію
    pushl %ebx
    call  cmain
    
    #  Забороняємо пеерривання
    cli  
    
hang:
    hlt          # Зупиняємо процесор
    jmp   hang   # На всякий випадок якщо процесор відновить роботу                 

.bss
    .lcomm stack, 0x4000             # Резервуємо місце під стек
    .comm  mbd, 4                    # Вазівник на структуру
    .comm  magic, 4                  # Місце під мігічне число
    .align 0x1000                    # Каталог сторінок і таблиці треба вирівняти до 4кб
    .lcomm page_table, 0x00401000    # Власне резервування місця під Таблиці сторінок і каталог таблиць
    
    