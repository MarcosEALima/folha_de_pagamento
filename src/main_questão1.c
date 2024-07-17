/*Este programa permite cadastrar informações de um número arbitrário de funcionários, 
calcular o pagamento mensal de cada um baseado no tipo de contrato (CLT ou terceirizado), 
e calcular o custo total da folha de pagamento da empresa.*/

#include <stdio.h>
#include <stdlib.h>

//define a estrutura Funcionario, que pode ser do tipo CLT ou terceirizado
typedef struct {
    char nome[50];
    int tipo; // 0 para CLT, 1 para terceirizado
    int contratos_assinados;
    float comissao_por_contrato;
    union {
        struct {
            float salario_fixo;
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
}

//função para calcular o pagamento total de um funcionário
float calcularPagamento(Funcionario f) {
    float pagamento = 0;
    if (f.tipo == 0) {
        pagamento = f.dados.clt.salario_fixo;
    } else {
        pagamento = f.dados.terceirizado.valor_hora * f.dados.terceirizado.horas_trabalhadas;
    }
    pagamento += f.contratos_assinados * f.comissao_por_contrato;
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
        printf("\nCadastrar funcionario %d:\n", i + 1);
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
