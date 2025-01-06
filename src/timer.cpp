/**
 * @file timer.cpp
 * @brief Zaman ölçüm işlemleri için kullanılan Timer sınıfının uygulaması.
 */

#include "timer.h"

Timer* Timer::_singleton = nullptr;

/**
 * @brief Timer sınıfının kurucusu.
 */
Timer::Timer() {}

/**
 * @brief Singleton tasarım deseni ile Timer nesnesi oluşturur.
 *
 * @return Timer sınıfının tekil örneği.
 */
Timer* Timer::get_singleton()
{
    if (_singleton == nullptr) {
        _singleton = new Timer();
    }
    return _singleton;
}

/**
 * @brief Zaman ölçümünü başlatır.
 */
void Timer::start()
{
    std::lock_guard<std::mutex> lock(mtx);
    start_time = std::chrono::high_resolution_clock::now();
}

/**
 * @brief Başlangıçtan itibaren geçen süreyi milisaniye cinsinden döndürür.
 *
 * @return Geçen süre (milisaniye).
 */
uint32_t Timer::now_ms()
{
    std::lock_guard<std::mutex> lock(mtx);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    return static_cast<uint32_t>(duration.count());
}

/**
 * @brief Başlangıçtan itibaren geçen süreyi mikrosaniye cinsinden döndürür.
 *
 * @return Geçen süre (mikrosaniye).
 */
uint64_t Timer::now_us()
{
    std::lock_guard<std::mutex> lock(mtx);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    return static_cast<uint64_t>(duration.count());
}

/**
 * @brief Başlangıçtan itibaren geçen süreyi nanosaniye cinsinden döndürür.
 *
 * @return Geçen süre (nanosaniye).
 */
uint64_t Timer::now_ns()
{
    std::lock_guard<std::mutex> lock(mtx);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    return static_cast<uint64_t>(duration.count());
}
