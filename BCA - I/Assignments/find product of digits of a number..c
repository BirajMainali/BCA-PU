
int main(void)
{
    int num, rem, prod = 1;

    printf("Enter a number: ");
    scanf("%d", &num);

    while(num != 0)
    {
        rem = num % 10;
        prod *= rem;
        num /=  10;
    }

    printf("%d", prod);

    return 0;
}
