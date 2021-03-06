/*
 *  chardev.h - определения ioctl.
 *
 *  Определения, которые здесь находятся, должны помещаться в заголовочный файл потому,
 *  что они потребуются как модулю ядра (chardev.c), так и 
 *  вызывающему процессу (ioctl.c)
 */

#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

/* 
 * Старший номер устройства. В случае использования ioctl,
 * мы уже лишены возможности воспользоваться динамическим номером,
 * поскольку он должен быть известен заранее.
 */
#define MAJOR_NUM 100

/* 
 * Операция передачи сообщения драйверу устройства
 */
#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, char *)
/*
 * _IOR означает, что команда передает данные
 * от пользовательского процесса к модулю ядра
 *
 * Первый аргумент, MAJOR_NUM -- старший номер устройства.
 *
 * Второй аргумент -- код команды
 * (можно указать иное значение).
 *
 * Третий аргумент -- тип данных, передаваемых в ядро
 */

/* 
 * Операция получения сообщения от драйвера устройства
 */
#define IOCTL_GET_MSG _IOR(MAJOR_NUM, 1, char *)
/* 
 * Эта команда IOCTL используется для вывода данных.
 * Нам по прежнему нужен буфер, размещенный в адресном пространстве 
 * вызывающего процесса, куда это сообщение должно быть переписано.
 */

/* 
 * Команда получения n-ного байта сообщения
 */
#define IOCTL_GET_NTH_BYTE _IOWR(MAJOR_NUM, 2, int)
/* 
 * Здесь команда IOCTL работает как на ввод, так и на вывод.
 * Она принимает от пользователя номер байта (n),
 * и возвращает n-ный байт сообщения (Message[n]). 
 */

/* 
 * Имя файла устройства
 */
#define DEVICE_FILE_NAME "char_dev"

#endif
