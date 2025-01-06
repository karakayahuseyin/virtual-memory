/**
 * @file timer.h
 * @brief Zaman ölçüm işlemleri için bir sınıf tanımı.
 */

#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <functional>
#include <chrono>
#include <mutex>
#include <cstdint>
#include <thread>

/**
 * @class Timer
 * @brief Yüksek çözünürlüklü zaman ölçüm işlemleri için kullanılan sınıf.
 */
class Timer {
public:
    /**
     * @brief Singleton tasarım deseni ile Timer nesnesi oluşturur.
     *
     * @return Timer sınıfının tekil örneği.
     */
    static Timer* get_singleton();

    /**
     * @brief Zaman ölçümünü başlatır.
     */
    void start();

    /**
     * @brief Başlangıçtan itibaren geçen süreyi milisaniye cinsinden döndürür.
     *
     * @return Geçen süre (milisaniye).
     */
    uint32_t now_ms();

    /**
     * @brief Başlangıçtan itibaren geçen süreyi mikrosaniye cinsinden döndürür.
     *
     * @return Geçen süre (mikrosaniye).
     */
    uint64_t now_us();

    /**
     * @brief Başlangıçtan itibaren geçen süreyi nanosaniye cinsinden döndürür.
     *
     * @return Geçen süre (nanosaniye).
     */
    uint64_t now_ns();

private:
    /**
     * @brief Timer sınıfının kurucusu.
     */
    Timer();

    /**
     * @brief Timer sınıfının yıkıcısı.
     */
    ~Timer() = default;

    static Timer* _singleton; /**< Singleton örneği. */

    std::chrono::high_resolution_clock::time_point start_time; /**< Zaman ölçümünün başlangıç noktası. */
    std::mutex mtx; /**< Zaman ölçümü sırasında eşzamanlılık için kullanılan kilit. */
};

#endif // TIMER_H
