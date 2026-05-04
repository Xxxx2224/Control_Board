#ifndef EMC_ERROR_H
#define EMC_ERROR_H

typedef enum {

  NO_ERROR = 0, /* Hata yok - Endüstri standardı olarak her zaman 0 olmalıdır */
  UNKNOWN_ERROR,           /* Bilinmeyen veya tanınmayan hata durumu */
  BAD_PARAMETER,           /* Fonksiyona geçersiz bir parametre gönderildi */
  ILLEGAL_USE_OF_NULL_PTR, /* Beklenmeyen Null pointer kullanımı (Örn: PID
                              struct'ı boş gelirse) */
  INDEX_OUT_OF_RANGE,      /* Dizi veya tampon bellek aralık dışı erişimi */
  BELOW_RANGE, /* Hesaplanan değer kabul edilebilir alt sınırın altında (Örn:
                  PID negatif çıkışı) */
  ABOVE_RANGE, /* Hesaplanan değer kabul edilebilir üst sınırın üzerinde (Örn:
                  PID aşımı/windup) */
  INCONSISTENT_VALUE, /* Mantıksal olarak tutarsız veri (Örn: Kp, Ki, Kd
                         katsayılarının mantıksız olması) */
  LIMIT_EXCEEDED,
  UNINITIALIZED,       /* Başlatılmamış modül veya değişken kullanımı */
  CATASTROPHIC_FAILURE /* Sistemi anında durduracak seviyede kritik hata */

} error_t;
#endif
