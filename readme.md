https://robojax.com/learn/arduino/?vid=robojax_VL53L0X_multiple

алгоритм
1. едем по маршруту, пока датчиком не будет x см
2. поворачиваем колеса исходя из маршрута (приемущество влево)
3. проезжаем до того как правым датчиком не будем определять пустоту
4. если правый датчик ничего не видит, поворачиваем колеса в направлении маршрута и едем

pio run --target upload && pio device monitor
ip 192.168.43.205