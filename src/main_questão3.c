#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    int tipo; // 0 para CLT, 1 para terceirizado
    int contratos_assinados;
    float comissao_por_contrato;
    float bonus_anual; // Adicionar campo para bônus anual
    union {
        struct {
            float salario_fixo;
            int horas_extras; // Adicionar campo para horas extras
            float taxa_hora_extra; // Adicionar campo para taxa de horas extras
        } clt;
        struct {
            float valor_hora;
            int horas_trabalhadas;
        } terceirizado;
    } dados;
} Funcionario;

void cadastrarFuncionario(Funcionario *f) {
    printf("Nome: ");
    scanf(" %[^\n]", f->nome);
    printf("Tipo (0 para CLT, 1 para terceirizado): ");
    scanf("%d", &f->tipo);
    if (f->tipo == 0) {
        printf("Salario fixo: ");
        scanf("%f", &f->dados.clt.salario_fixo);
        printf("Horas extras: ");
        scanf("%d", &f->dados.clt.horas_extras);
        printf("Taxa por hora extra: ");
        scanf("%f", &f->dados.clt.taxa_hora_extra);
    } else {
        printf("Valor por hora: ");
        scanf("%f", &f->dados.terceirizado.valor_hora);
        printf("Horas trabalhadas: ");
        scanf("%d", &f->dados.terceirizado.horas_trabalhadas);
    }
    printf("Contratos assinados: ");
    scanf("%d", &f->contratos_assinados);
    printf("Comissao por contrato: ");
    scanf("%f", &f->comissao_por_contrato);
    printf("Bonus anual: ");
    scanf("%f", &f->bonus_anual); // Entrada para bônus anual
}

float calcularPagamento(Funcionario f) {
    float pagamento = 0;
    if (f.tipo == 0) {
        pagamento = f.dados.clt.salario_fixo;
        pagamento += f.dados.clt.horas_extras * f.dados.clt.taxa_hora_extra; // Cálculo de horas extras
    } else {
        pagamento = f.dados.terceirizado.valor_hora * f.dados.terceirizado.horas_trabalhadas;
    }
    pagamento += f.contratos_assinados * f.comissao_por_contrato;
    pagamento += f.bonus_anual / 12; // Distribuição do bônus anual ao longo do ano (mensal)
    return pagamento;
}

int main() {
    int n;
    printf("Quantos funcionarios deseja cadastrar: ");
    scanf("%d", &n);

    Funcionario* funcionarios = (Funcionario*) malloc(n * sizeof(Funcionario));

    for(int i = 0; i < n; i++) {
        printf("\nCadastrar funcionario %d:\n", i+1);
        cadastrarFuncionario(&funcionarios[i]);
    }

    float folha_total = 0;
    for (int i = 0; i < n; i++) {
        float total_a_receber = calcularPagamento(funcionarios[i]);
        printf("\n%s recebera: R$%.2f\n", funcionarios[i].nome, total_a_receber);
        folha_total += total_a_receber;
    }

    printf("\nCusto total da folha de pagamento da empresa: R$%.2f\n", folha_total);

    free(funcionarios);
    return 0;
}
