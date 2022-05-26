#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	float num1, num2;
	char op;

	printf("Enter operator either + or - or * or divide : ");
	fflush(stdout);
	scanf("%c", &op);
	printf("Enter two operands: ");
	scanf("%f %f", &num1, &num2);

	switch(op)
	{
		case '+':
			printf("%.lf + %.1f = %.1f", num1, num2, num1 + num2);
			break;
		case '-':
			printf("%.lf - %.1f = %.1f", num1, num2, num1 - num2);
			break;
		case '*':
			printf("%.lf * %.1f = %.1f", num1, num2, num1 * num2);
			break;
		case '/':
			if(num2 != 0)
			{
				printf("%.lf / %.1f = %.1f", num1, num2, num1 / num2);
			}
			else
			{
				printf("Error! division by zero");
			}
			break;
		default:
			printf("Error! operator is not correct");
			break;
	}

	return EXIT_SUCCESS;
}
