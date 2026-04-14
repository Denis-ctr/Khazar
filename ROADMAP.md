# Khazar OS - İnkişaf Yol Xəritəsi (Roadmap)

`Khazar OS` layihəsi üçün x86_64 mühitində sıfırdan yazıla biləcək təməl mexanizmləin qurulması üçün hazırlanmış xüsusi inkişaf addımları:

---

## Mərhələ 1: CPU Kəsilmələri və Xətaları (Interrupts & Exceptions) - *Hazırkı hədəf*

Sistem hazırda 64-bit olaraq yüklənir (boot), GDT və IDT strukturları mövcuddur. Ancaq istənilən əsas xəta (məsələn: Sıfıra bölünmə - *Divide by Zero*) zamanı CPU qapanır. Bunun qarşısını almaq üçün:

*   **[x] ISR-lərin (Interrupt Service Routines) yazılması:** Assembly və C-ni birləşdirərək ilk 32 IDT girişini (Exceptions: Page Fault, Double Fault, General Protection Fault və s.) təyin etmək. Qeyd olunan səhvlər baş verdikdə ekranın yuxarı hissəsində xətanın adının və yaddaş ünvanının (registry dump) çıxarılması.
*   **[ ] PIC (Programmable Interrupt Controller) Re-mapping:** Xarici qurğuların (Hardware) kəsilmələri ilə CPU daxili xətalarının toqquşmaması üçün İRQ (Interrupt Request) nömrələrini (Master və Slave PIC) 32-47 nömrəli slotlara sürüşdürmək.

## Mərhələ 2: Baza Sürücüləri (Basic Drivers)

Kəsilmələr aktiv və təhlükəsiz olduqdan sonra artıq xarici siqnallara cavab vermək olar:

*   **[ ] Klaviatura Sürücüsü (PS/2):** İRQ1 kanalından qəbul edilən "scan code"-ları öyrənmək, onları `char` (ASCII) tipinə çevirib terminala məqalə və komandalar yazmağı planlamaq.
*   **[ ] Timer (PIT - Programmable Interval Timer):** CPU-nun daxili idarəetməsini sabitləşdirmək üçün İRQ0 vasitəsi ilə "tick" intervalı yaratmaq. `sleep(ms)` və `get_time()` kimi vacib sistem funksiyaları üçün təməl atmaq.

## Mərhələ 3: Yaddaşın İdarə Olunması (Memory Management)

Əməliyyat sisteminin ürəyi sayılan kompleks mərhələ:

*   **[ ] Physical Memory Manager (PMM):** GRUB (Multiboot) məlumatlarından istifadə edərək RAM-da istifadəyə yararlı yaddaşları tapmaq və "Page Frame Allocator" vasitəsi ilə (məsələn, Bitmap ilə) səhifələrə (4KB) bölmək.
*   **[ ] Virtual Memory Manager / Paging (VMM):** 64-bit Long Mode üçün "4-level Paging" sistemini tam qurmaq və virtual ünvanları fiziki ünvanlara mapping-ə başlamaq.
*   **[ ] Heap Allocator (Dinamik Yaddaş):** Komponentlər üçün daxili yaddaş bölüşdürücüsü: `kmalloc()` və `kfree()` funksiyalarının yazılması.

## Mərhələ 4: Çoxtapşırıqlılıq və İstifadəçi Proqramları (Multitasking & User Space)

Khazar OS sisteminin proqram təminatı işlədə bilməsi üçün mühit yaratmaq:

*   **[ ] Task Mühiti və Context Switching:** PIT vasitəsi ilə saniyədə yüz dəfə qısa dondurmalar edərək registr və stack dəyişməklə proseslər arası paylanmış iş rejimi yaratmaq (Multithreading/Multitasking).
*   **[ ] User Mode (Ring 3):** Ring 0-dan (Kernel) aşağı imtiyazlı Ring 3-ə təhlükəsiz keçmək.
*   **[ ] Sistem Çağırışları (Syscalls):** İstifadəçinin proseslərinin (proqramlarının) ekran, klaviatura və RAM istəyini Kernel-ə "Syscall" ilə etməsini təmin etmək.

## Mərhələ 5: Fayl Sistemi (File Systems & Storage)

*   **[ ] PCI Əlaqəsi (PCI Bus scanning):** Ana kart daxilindəki qurğuları axtaracaq və avadanlığı tapacaq kodun (driver API) qurulması.
*   **[ ] Mass Storage (Disk sürücüləri):** ATA (IDE) və ya SATA (AHCI) yaddaş qurğularının disk sektorlarının oxunub-yazılması.
*   **[ ] Virtual File System (VFS) & İlkin Format:** Kernel-in fayl strukturunu tanımasına kömək üçün öncə VFS abstraksiyası yaratmaq, daha sonra `FAT32` və ya ext2 formatlarını quraşdırmaq.

---

### Oxumaq və Öyrənmək üçün Resurslar (Mənbələr)

Khazar OS inkişaf etdirərkən bu 5 mənbə əsas bələdçiniz olacaq:

1. **OSDev.org Vikisi:** Həm nəzəri, həm praktiki ən spesifik əməliyyat sistemi inkişaf bazası. Bütün sistem arxitekturası arayışları buradadır.
   🔗 [wiki.osdev.org](https://wiki.osdev.org/)

2. **Writing an OS in Rust (Müəllif: Philipp Oppermann):** Rust üzərindən izah etsə də, 64-bit və Paging mexanikasını qrafiklərlə, ardıcıl və məntiqlə ən yaxşı öyrədən müasir resursdur.  
   🔗 [os.phil-opp.com](https://os.phil-opp.com/)

3. **JamesM's Kernel Development Tutorials:** C dilində 32-bit x86 sistemini klassikləşdirilmiş şəkildə anladan tutorial. "Heap", "kmalloc" strukturunu anlamağa dəstək olacaq.
   🔗 [http://www.jamesmolloy.co.uk/tutorial_html/](http://www.jamesmolloy.co.uk/tutorial_html/)

4. **"Operating Systems: Three Easy Pieces":** Əməliyyat sistemlərində faylların, virtual yaddaşın və "Time-Sharing"-in Riyazi və Kompüter elmləri baxımından necə analiz olunduğunu izah edən müstəsna kitab (pulsuz PDF versiyası).
   🔗 [OSTEP Free PDF](http://pages.cs.wisc.edu/~remzi/OSTEP/)

5. **Intel® 64 and IA-32 Architectures Software Developer Manuals:** Bir başa İntel-ə məxsus ən dəqiq rəhbər sənədlər toplusu. GDT bitləri və digər Assembly dərsləri daxildir.
   🔗 [Intel SDM](https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
