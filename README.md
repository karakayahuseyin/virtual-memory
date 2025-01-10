### **Proje Hakkında**

Bu proje, **işletim sistemleri** alanında bellek yönetiminin temel prensiplerini anlamak ve uygulamaya yönelik bir çalışma olarak geliştirilmiştir. Projenin ana hedefi, **Sanal Bellek Yöneticisi** tasarlayarak dinamik bellek tahsisi, serbest bırakma, bellek bloklarının birleşimi gibi işlemleri gerçekleştirmek ve bu işlemlerin performansını ölçmektir.

Proje, hem kullanıcı komutlarını işleyebilen bir **Komut Satırı Arayüzü (CLI)** hem de otomatik işleyiş için **dosya tabanlı komut modunu** desteklemektedir. Ayrıca, gömülü sistemler ve masaüstü sistemlerde kullanılabilirliği hedef alınmıştır.

İşletim Sistemleri dersi dönem sonu projesi olarak hazırlanmıştır. Katkı verenler:
- [Eren Karakuş](https://github.com/eren-karakus0)
- [Yusuf Bilal Usta](https://github.com/yusufbilalusta)
- [A. Hamza Gündoğdu](https://github.com/hamzagnd)

---

### **Amaç**

- Bellek tahsisi ve serbest bırakma işlemlerini yönetmek.  
- Bellek bloklarının birleşimi ve verimli kullanımını sağlamak.  
- Kullanıcı komutlarını işleyerek bellek manipülasyonu yapmak.  
- Performansı ölçmek için zamanlayıcı mekanizmasını uygulamak.  
- Geliştirilen modülün hem gömülü sistemlerde hem de masaüstü sistemlerde çalışabilir olması.  

---

### **Kullanım**

#### **Komut Satırı Modu (CLI)**
Kullanıcı, komutları doğrudan CLI üzerinden girebilir ve sonuçları anında görebilir. Çalıştırmak için ```./program --cli```

- **`PRINT`**: Mevcut bellek bloklarını listeler.
- **`DATA8/16/32/64`**: Yeni veri bloğu oluşturur.  
  Örnek: `DATA16 BLOCK1` 
- **`FREE [block_name]`**: Belirtilen veri bloğunu serbest bırakır.  
  Örnek: `FREE BLOCK1`
- **`GET [block_name]`**: Belirtilen bloğun içeriğini görüntüler.  
  Örnek: `GET BLOCK1`
- **`SET [block_name] [data]`**: Veriyi günceller.  
  Örnek: `SET BLOCK1 0x1234`

#### **Dosya Modu**
Kullanıcı, komutları bir dosyaya yazar ve program bu dosyayı işleyerek komutları sırasıyla çalıştırır. Çalıştırmak için ```./program --file file.txt"```

- **Dosya Formatı**: Her bir komut, dosyada bir satırda olmalıdır. 
  Örnek:
  - DATA8 AA 0x11
  - DATA16 BB 0x12
  - PRINT
  - GET AA
  - FREE BB
  - PRINT
