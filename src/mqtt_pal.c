#include <mqtt.h>

#ifdef __unix__

#include <errno.h>

ssize_t mqtt_pal_sendall(int fd, void* buf, size_t bufsz, int flags) {

}
ssize_t mqtt_pal_recvall(int fd, void* buf, size_t bufsz, int flags) {
    const void const *start = buf;
    ssize_t rv;
    do {
        rv = recv(fd, buf, bufsz, 0);
        if (rv > 0) {
            /* successfully read bytes from the socket */
            buf += rv;
            bufsz -= rv;
        } else if (rv < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
            /* an error occurred that wasn't "nothing to read". */
            return MQTT_ERROR_SOCKET_ERROR;
        }
    } while (rv > 0);

    return buf - start;
}

#endif