/*O codigo faz as mesmas funções que o da questao 1 
e a lógica inclui horas extras e divisão do bônus anual*/

#include <stdio.h>
#include <stdlib.h>

//define a estrutura Funcionario, que pode ser do tipo CLT ou terceirizado
typedef struct {
    char nome[50];
    int tipo; //0 para CLT, 1 para terceirizado
    int contratos_assinados;
    float comissao_por_contrato;
    float bonus_anual; //campo para bônus anual
    union {
        struct {
            float salario_fixo;
            int horas_extras; //campo para horas extras
            float taxa_hora_extra; //campo para taxa de horas extras
        } clt;
        struct {
            float valor_hora;
            int horas_trabalhadas;
        } terceirizado;
    } dados;
} Funcionario;

//dunção para cadastrar os dados de um funcionário
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
    scanf("%f", &f->bonus_anual); //entrada para bônus anual
}

//função para calcular o pagamento total de um funcionário
float calcularPagamento(Funcionario f) {
    float pagamento = 0;
    if (f.tipo == 0) {
        pagamento = f.dados.clt.salario_fixo;
        pagamento += f.dados.clt.horas_extras * f.dados.clt.taxa_hora_extra; //calculo de horas extras
    } else {
        pagamento = f.dados.terceirizado.valor_hora * f.dados.terceirizado.horas_trabalhadas;
    }
    pagamento += f.contratos_assinados * f.comissao_por_contrato;
    pagamento += f.bonus_anual / 12; //distribuição do bônus anual ao longo do ano (mensal)
    return pagamento;
}

int main() {
    int n;
    printf("Quantos funcionarios deseja cadastrar: ");
    scanf("%d", &n);

    //aloca memória para o número de funcionários
    Funcionario* funcionarios = (Funcionario*) malloc(n * sizeof(Funcionario));

    //Loop para cadastro dos funcionários
    for(int i = 0; i < n; i++) {
        printf("\nCadastrar funcionario %d:\n", i+1);
        cadastrarFuncionario(&funcionarios[i]);
    }

    float folha_total = 0;
    //Loop para calcular e exibir o pagamento de cada funcionário
    for (int i = 0; i < n; i++) {
        float total_a_receber = calcularPagamento(funcionarios[i]);
        printf("\n%s recebera: R$%.2f\n", funcionarios[i].nome, total_a_receber);
        folha_total += total_a_receber;
    }

    //exibe o custo total da folha de pagamento da empresa
    printf("\nCusto total da folha de pagamento da empresa: R$%.2f\n", folha_total);

    //libera a memória alocada
    free(funcionarios);
    return 0;
}
