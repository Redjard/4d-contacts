#ifndef CURVE25519_H
#define CURVE25519_H

typedef unsigned char curve25519_key[32];

#ifdef __cplusplus
extern "C" {
#endif

void curve25519_donna(curve25519_key mypublic, const curve25519_key secret, const curve25519_key basepoint);
void curve25519_donna_basepoint(curve25519_key mypublic, const curve25519_key secret);

#ifdef __cplusplus
}
#endif

#endif /* CURVE25519_H */

