#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef enum {
    CLT,
    TERCEIRIZADO
} TipoContrato;

typedef struct {
    char nome[100];
    TipoContrato tipp;
    union {
        struct{
            double salario;
        } clt;
    }
}