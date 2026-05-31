# Control Board Mimarisi

> Sürdürülebilir, performanslı, genişletilebilir ve çoklu donanım desteği sunabilen güçlü bir mimari inşa ederek bir kontrol kartı gelistirmekteyim. Bu projede ulaşmaya çalıştığım mevcut hedeflerimi ve teknik prensiplerimi aşağıdaki kategorilerde özetledim. Bu hedefleri, proje büyüdükçe şekillendirmeye ve geliştirmeye devam ettirmeye çalışacağım.

## Mimari Felsefe

Bu proje, donanıma sıkı sıkıya bağlı (tightly coupled) gömülü yazılım yaklaşımlarından uzaklaşmaktadır. Bunun yerine `App/` dizini etrafında şekillenen ölçeklenebilir bir mimari uygular.

Mimari, birbirinden bağımsız, izole katmanlara ayrılmıştır:
*   **Control:** Üst düzey kontrol döngüleri (Örn: Ayrık zamanlı PID kontrolörleri).
*   **Core:** İş mantığı ve ana State Machine (durum makinesi) orkestrasyonu.
*   **Drivers:** Düşük seviyeli donanım etkileşimleri.
*   **HAL (Donanım Soyutlama Katmanı):** Core ile Drivers katmanı arasında POSIX standartlarına uyacak şekilde bir köprü kurmak.
*   **Test:** `CppUTest` kullanılarak yapılan kapsamlı Unit testlerinin yanı sıra Entegrasyon, HIL (Hardware-in-the-Loop) ve SIL (Software-in-the-Loop) test süreçleri.

## Önemli Mühendislik Kararları

### 1. Opaque Pointer ve Fonksiyon Pointer'ları ile Donanım İzolasyonu
İş mantığının donanım register'larına veya üretici HAL katmanına doğrudan temas etmemesini sağlamak için POSIX standartlarından ilham alan bir soyutlama katmanı kullanıyoruz.

*   **Çalıştırma (Execution):** Geliştirici, standart bir API (örn: `motor_set_pwm()`) üzerinden bir motora komut gönderebilir. Arka planda bu özel HAL katmanı, fonksiyon pointer'ları aracılığıyla ilgili spesifik sürücü implementasyonunu çağırır.
*   **Donanım Bağlama (Hardware Binding):** Fonksiyon pointer'larının çözümlenmesi esnek olacak şekilde tasarlanmıştır; derleme zamanında (sensör/donanım tanımlamaları aracılığıyla) veya çalışma zamanında dinamik donanım tespiti ("Who am I" sorgusu) ile yapılabilir.
*   **Kesme (Interrupt) Ayrıştırması:** Kesme Servis Rutinleri (ISR'ler) tamamen soyutlanmıştır. Bir kesme tetiklendiğinde, sürücü seviyesinde değil, Core katmanında tanımlanmış ve HAL'e kaydedilmiş (register edilmiş) bir *callback* fonksiyonu çalıştırılır. Bu sayede geliştiricilerin, uygulamaya özel kesme mantığını işlemek için sürücü seviyesindeki dosyalara müdahale etmesine gerek kalmaz.

### 2. Çift Çekirdekli Asimetrik Çoklu İşlem (AMP)
STM32H755 (CM7/CM4) için tasarlanmıştır:
*   **Cortex-M7:** Ana işlem yükünü, karmaşık kontrol algoritmalarını ve sistem orkestrasyonunu üstlenir.
*   **Cortex-M4:** Destekleyici görevleri, gerçek zamanlı çevresel birim (peripheral) yönetimini veya devredilmiş veri işleme süreçlerini yöneten bir yardımcı işlemci (coprocessor) olarak görev yapar.

### 3. Sürekli Zamandan Ayrık Zamana Kontrol Sistemleri
PID gibi kontrol döngüleri, sürekli zaman modellerinin sistem adım sürelerine (step times) göre ayrıklaştırılmasıyla (discretization) uygulanır. Bu yaklaşım, farklı donanım çalışma hızlarında bile deterministik ve matematiksel olarak doğru davranış sergilenmesini sağlar.

## Kod Okunabilirliği, Kalitesi, Güvenlik ve Test

Görev açısından kritik bir güvenilirliği hedefleyen bu kod tabanı, aşağıdaki standartlara sıkı sıkıya bağlıdır:
*   **Standartlar:** API tasarımı için POSIX uyumluluğu ve güvenli C programlama için MISRA C yönergeleri.
*   **Statik Analiz:** Tanımsız davranışları (undefined behavior) ve MISRA ihlallerini erken aşamada yakalamak için `Cppcheck` ve `clang-tidy` gibi araçlar kullanılarak sıkı bir kod denetimi (linting) yapılandırılmıştır.
*   **Birim Testi (Unit Testing):** `Test/` katmanı, donanımdan bağımsız olarak yazılım mantığını doğrulamak için **CppUTest** kullanır.

## Modüler Derleme Sistemi (CMake)

Proje, oldukça granüler bir CMake yapılandırması kullanır.
*   **Mevcut Durum:** Her katmanın kendi `CMakeLists.txt` dosyası vardır ve ana projeye kütüphane olarak eklenir. Şu anda hızlı geliştirme süreci için `INTERFACE` kütüphaneleri kullanılarak yapılandırılmıştır.
*   **Yol Haritası:** İç yapıyı gizleyen (Opaque pointer mimarisi) statik/paylaşımlı kütüphanelere geçiş yapılması planlanmaktadır. Bu sayede derleme süreleri ciddi oranda düşürülecek ve çok daha sıkı bir sınır kapsüllemesi (boundary encapsulation) sağlanacaktır.

---
*Sürdürülebilirlik, güvenlik ve donanım bağımsızlığı odaklı geliştiriliyor.*
