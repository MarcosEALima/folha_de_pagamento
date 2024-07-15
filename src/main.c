#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char nome[50];
    int tipo; // 0 para CLT, 1 para terceirizado
    float salario_fixo; // Para CLT
    float valor_hora; // Para terceirizados
    int horas_trabalhadas; // Para terceirizados
    int contratos_assinados;
    float comissao_por_contrato;
} Funcionario;

void cadastrarFuncionario(Funcionario *f) {
    printf("Nome: ");
    scanf(" %[^\n]", f->nome);
    printf("Tipo (0 para CLT, 1 para terceirizado): ");
    scanf("%d", &f->tipo);
    if (f->tipo == 0) {
        printf("Salario fixo: ");
        scanf("%f", &f->salario_fixo);
    } else {
        printf("Valor por hora: ");
        scanf("%f", &f->valor_hora);
        printf("Horas trabalhadas: ");
        scanf("%d", &f->horas_trabalhadas);
    }
    printf("Contratos assinados: ");
    scanf("%d", &f->contratos_assinados);
    printf("Comissao por contrato: ");
    scanf("%f", &f->comissao_por_contrato);
}

float calcularPagamento(Funcionario f) {
    float pagamento = 0;
    if (f.tipo == 0) {
        pagamento = f.salario_fixo;
    } else {
        pagamento = f.valor_hora * f.horas_trabalhadas;
    }
    pagamento += f.contratos_assinados * f.comissao_por_contrato;
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