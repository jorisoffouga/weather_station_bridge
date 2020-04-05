# weather_station_bridge

This projet provides serial interface and dbus for communicate with [https://github.com/jorisoffouga/weather_monitor](weather_monitor)
and [https://github.com/jorisoffouga/zephyr-application/tree/master/samples/weather_station](wheater_station)

I. Install dependancies

C-Periphery

```
$: git clone https://github.com/jorisoffouga/c-periphery -b add/pkgconfig
$: cd c-periphery
$: cmake -DBUILD_SHARED_LIBS=ON ..
$: make
$: sudo make install
```

libsystemd

```
$: sudo apt install libsystemd-dev
```

II. Run Application

```
$: ./weather-station-bridge -p <tty interface serial of stm32>
```
