#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define STACK_SIZE 50
#define e 2.718281
int top = -1;
int top2 = -1;
float FloatStack[STACK_SIZE];
char stack[STACK_SIZE];
int precedence(char op) {
    switch(op) {
        case '^':
            return 4; // Üstel
        case '*':
        case '/':
            return 2; // Çarpma, bölme, mod
        case '+':
        case '-':
            return 1; // Toplama, çıkarma
        case 's':
        case 'c':
        case 't':
        case 'l':
        case 'a':
        case 'A':
        case 'C':
        case 'T':
         // Ters trigonometrik fonksiyonlar
            return 3; // Trigonometrik fonksiyonlar ve logaritma
        default:
            return 0; // Diğer durumlar için
    }
}


float **allocateMatrix(int satir,int sutun){
    int i;
    float **matris=(float**)malloc(sizeof(float*)*satir);
    for (i=0; i<satir; i++) {
        matris[i]=(float*)calloc(sutun, sizeof(float));
    }
    return matris;
}
void freeMatrix(float **matris,int satir){
    int i;
    for (i=0; i<satir; i++) {
        free(matris[i]);
    }
    free(matris);
}
void matrisiYazdırma(float **matris,int satir,int sutun){
    int i,j;
    printf("Matris:\n");
    for (i=0; i<satir; i++) {
        for (j=0; j<sutun; j++) {
            printf("%8.3f ",matris[i][j]);
        }
        printf("\n");
    }
}
float Determinant(float **matris,int n){
    if (n==1) {
        return matris[0][0];
    }else if(n==2){
        return matris[0][0]*matris[1][1]-matris[0][1]*matris[1][0];
    }else{
        float det = 0;
                float **temp = allocateMatrix(n - 1, n - 1);
                int sign = 1;

                for (int i = 0; i < n; i++) {
                    int temp_row = 0;

                    for (int row = 1; row < n; row++) {
                        int temp_col = 0;

                        for (int col = 0; col < n; col++) {
                            if (col != i) {
                                temp[temp_row][temp_col++] = matris[row][col];
                            }
                        }
                        temp_row++;
                    }

                    det += sign * matris[0][i] * Determinant(temp, n - 1);
                    sign *= -1;
                }
        freeMatrix(temp, n - 1);
        return det;
    }
}
int inverseMatrix(float **matris, int n, float **inverse) {
    int i, j, row, col;
    float det = Determinant(matris, n);
    if (det == 0) {
        printf("Matrisin tersi yoktur (det=0)\n");
        return 0;
    }

    float **temp = allocateMatrix(n, n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int temp_i = 0;
            float **minor = allocateMatrix(n - 1, n - 1);
            for (row = 0; row < n; row++) {
                if (row != i) {
                    int temp_j = 0;
                    for (col = 0; col < n; col++) {
                        if (col != j) {
                            minor[temp_i][temp_j++] = matris[row][col];
                        }
                    }
                    temp_i++;
                }
            }
            float sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            temp[i][j] = sign * Determinant(minor, n - 1);
            freeMatrix(minor, n - 1);
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            inverse[j][i] = temp[i][j] / det;
        }
    }

    freeMatrix(temp, n);
    printf("Matrisin tersi alındı.\n");
    return 1;
}
void push(char data){
    if (top==STACK_SIZE) {
        printf("stack full");
        return ;
    }
    stack[++top]=data;
}
void pushFloat(float data){
    if (top2==STACK_SIZE) {
        printf("stack full");
        return ;
    }
    FloatStack[++top2]=data;
}
char pop(void){
    char deger;
    if (top==-1) {
        exit(1);
    }
    deger=stack[top--];
    return deger;
}
float Floatpop(void){
    float deger;
    if (top2==-1) {
        exit(1);
    }
    deger=FloatStack[top2--];
    return deger;
}
int isEmpty(void){
    return (top==-1);
}
char peek(void){
    if (top!=-1) {
        return stack[top];
    }else{
        exit(1);
    }
}
int factoriel(int n){
    int f=1,i;
    for (i=2; i<=n; i++) {
        f*=i;
    }
    return f;
}
int isOperator(char ch){
    if (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^') {
        return 1;
    }else{
        return 0;
    }
}
float EvaluatePostfix(float x,char *postfix,char *logbases){
    int i;
    float operand1 = 0.0,operand2=0.0,result,sayi=0;
    for(i=0;i<strlen(postfix);i++){
       if(isdigit(postfix[i]) || postfix[i] == 'x' || postfix[i] == 'e'){
            if(postfix[i] == 'x' || postfix[i] == 'e'){
                if(postfix[i] == 'x'){
                    pushFloat(x);
                }
                else{
                    pushFloat(e);
                }
                
            }
            else{
                sayi = 0.0;
                while (isdigit(postfix[i])) {
                if(isdigit(postfix[i])){
                    sayi = (sayi * 10) + (postfix[i] - '0');
                    i++;
                }
            }
                pushFloat(sayi);
            i--;
            }
        }
        else if(postfix[i] == ' '){
            continue;
        }
        else{
            if(isOperator(postfix[i])){
                    operand2 = Floatpop();
                    operand1 = Floatpop();
                }
            else{
                    operand2 = Floatpop();
                }
            switch(postfix[i]){
                case '^':
                    pushFloat(pow(operand1,operand2));
                    break;
                case '*':
                    pushFloat(operand1*operand2);
                    break;
                case '/':
                    pushFloat(operand1/operand2);
                    break;
                case '-':
                    pushFloat(operand1 - operand2);
                    break;
                case '+':
                    pushFloat(operand1 + operand2);
                    break;
                case 's':
                    pushFloat(sin(operand2));
                    break;
                case 'c':
                    pushFloat(cos(operand2));
                    break;
                case 't':
                    pushFloat(tan(operand2));
                    break;
                case 'l':
                    if(logbases[0] == 'x'){
                        pushFloat(log(operand2)/log(x));
                    }
                    else{
                        pushFloat(log(operand2)/log(logbases[0]-'0'));
                    }
                    break;
                case 'A':
                    pushFloat(asin(operand2));
                    break;
                case 'C':
                    pushFloat(acos(operand2));
                    break;
                case 'T':
                    pushFloat(atan(operand2));
                default:
                    printf("hata\n");
                    break;
            }
        }
    }
    result = Floatpop();
    return result;
}
void InfixToPostfix(char *metin,char *postfix,char *logbases){
    int i,j=0;
    char next;
    for(i=0;metin[i] != '\0';i++){
        if(metin[i] == '('){
            push(metin[i]);
            postfix[j++] = ' ';
        }
        else if(metin[i] == ')'){
            while((next = pop()) != '('){
                postfix[j++] = ' ';
                postfix[j++] = next;
            }
        }
        else if(!(isdigit(metin[i])) && metin[i] != 'e' && metin[i]!= 'x'&& metin[i]!= '.')
        {
            while(isEmpty() == 0 && precedence(stack[top]) >= precedence(metin[i])){
                postfix[j++] = pop();
            }
            if(isOperator(metin[i])){
                push(metin[i]);
                postfix[j++] = ' ';
            }
            else if (strncmp(&metin[i], "arcsin", 6) == 0) {
                push('A');
                postfix[j] = ' ';
                j++;
                i += 5;
            } else if (strncmp(&metin[i], "arccos", 6) == 0) {
                push('C');
                postfix[j] = ' ';
                j++;
                i += 5;
            } else if (strncmp(&metin[i], "arctan", 6) == 0) {
                push('T');
                postfix[j] = ' ';
                j++;
                i += 5;
            }
            else if(metin[i] == 'l'){
                push(metin[i]);
                i = i + 4;
                *logbases = metin[i];
                logbases++;
                postfix[j++] = ' ';
                
            }
            else{
                push(metin[i]);
                postfix[j++] = ' ';
                i+=2;
            }
        }
        else{
            postfix[j++] = metin[i];
        }

    }
    while(top != -1){
        postfix[j++]=pop();
    }
    printf("\npostfix ifade : %s\n",postfix);
}
void BiSection(char* postfix,char *logbases){
    int flag=1,j=1,n=0;
    float a,b;
    float hata = 0.0,mevcut_hata,adaykok=0.0;
    printf("Lütfen kapalı aralığı giriniz\n");
    scanf("%f %f",&a,&b);
    while (flag==1) {
        if (EvaluatePostfix(a,postfix,logbases)*EvaluatePostfix(b,postfix,logbases) < 0) {
            system("clear");
            printf("Girdiğiniz aralıkta kök vardır\n");
            printf("Lütfen kabul edilebilir hata miktarını giriniz\n");
            scanf("%f",&hata);
            flag--;
        }else{
            printf("girdiğiniz aralıkta kök yoktur.Lütfen tekrar deneyiniz\n");
            scanf("%f %f",&a,&b);
        }
    }
    do {
        adaykok=(a+b)/2;
        j*=2;
        mevcut_hata=(b-a)/j;
        if(EvaluatePostfix(adaykok,postfix,logbases)*EvaluatePostfix(b,postfix,logbases) < 0){
            a = adaykok;
        }
        else if((EvaluatePostfix(adaykok,postfix,logbases)*EvaluatePostfix(a,postfix,logbases)) < 0){
            b = adaykok;
        }
        n++;
        printf("\n %d.iterasyondaki hata : %lf\n",n,mevcut_hata);
    } while (mevcut_hata > hata);
    printf("\naradıgımız kök : %f\n",adaykok);
}
void RegulaFalsi (float x,char* postfix,char *logbases){
    int flag=1;
    float a,b;
    float hata = 0.0,adaykok[2]={0,0};
    printf("lütfen kapalı aralığı giriniz\n");
    scanf("%f %f",&a,&b);
    while (flag==1) {
        if (EvaluatePostfix(a,postfix,logbases)*EvaluatePostfix(b,postfix,logbases) < 0) {
            system("clear");
            printf("Girdiğiniz aralıkta kök vardır\n");
            printf("Lütfen kabul edilebilir hata miktarını giriniz\n");
            scanf("%f",&hata);
            flag--;
        }else{
            printf("girdiğiniz aralıkta kök yoktur.Lütfen tekrar deneyiniz\n");
            scanf("%f %f",&a,&b);
        }
    }
    do {
        adaykok[0]=adaykok[1];
        adaykok[1]=((a * EvaluatePostfix(b,postfix,logbases)) - (b * EvaluatePostfix(a,postfix,logbases)))/(EvaluatePostfix(b,postfix,logbases)-EvaluatePostfix(a,postfix,logbases));
        if (EvaluatePostfix(a, postfix, logbases)*EvaluatePostfix(adaykok[1], postfix, logbases)<0) {
            b = adaykok[1];
        }else if(EvaluatePostfix(adaykok[1],postfix,logbases)*EvaluatePostfix(b,postfix,logbases)<0){
            a= adaykok[1];
        }
        
    } while (fabs(adaykok[1]-adaykok[0]) > hata);
    printf("kökümüz : %lf\n",adaykok[1]);
    
}
void NewtonRaphson(float x,char* postfix,char *logbases){
    float bdeger,kokaday = 2.0,hata,dx,temp = 0;
    printf("Lütfen başlangıç değerini giriniz: ");
    scanf("%f",&bdeger);
    printf("lütfen hata değerinin giriniz:");
    scanf("%f",&hata);
    printf("Türev icin ileri farklar kullanıyoruz bu yüzden dx değeri giriniz:");
    scanf("%f",&dx);
    do {
        temp=bdeger;
        float fx=EvaluatePostfix(bdeger, postfix, logbases);
        float fx_dx=EvaluatePostfix(bdeger+dx, postfix, logbases);
        float turev=(fx_dx-fx)/dx;
        kokaday=bdeger-(fx/turev);
        bdeger=kokaday;
    } while (fabs(kokaday - temp) > hata);
    printf("kok degerimiz : %f",kokaday);
}
void TersMatris(void) {
    int boyut, i, j;
    printf("Matrisin boyutunu giriniz: ");
    scanf("%d", &boyut);

    float **matris = allocateMatrix(boyut, boyut);
    float **tersMatris = allocateMatrix(boyut, boyut);

    for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut; j++) {
            printf("Matrisin [%d][%d] elemanını giriniz: ", i + 1, j + 1);
            scanf("%f", &matris[i][j]);
        }
    }

    if (inverseMatrix(matris, boyut, tersMatris)) {
        printf("\nMatrisin Tersi:\n");
        matrisiYazdırma(tersMatris, boyut,boyut);
    } else {
        printf("\nMatrisin tersi yoktur (det=0).\n");
    }

    freeMatrix(matris, boyut);
    freeMatrix(tersMatris, boyut);
}
void CholeskyYontemi(void){
    int n,flag=-1,i,j,k;
    float toplam,val;
    
    printf("Matrisin boyutunu giriniz\n");
    scanf("%d",&n);
    float **matris=allocateMatrix(n, n);
    float **L=allocateMatrix(n, n);
    printf("Simetrik pozitif tanımlı matrisin elemanlarını giriniz:\n");
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("Matrisin [%d][%d].elemanını giriniz\n",i+1,j+1);
            scanf("%f",&matris[i][j]);
        }
    }
    for (i = 0; i < n && flag; i++) {
            for (j = 0; j <= i && flag; j++) {
                toplam = 0.0;
                for (k = 0; k < j; k++) {
                    toplam += L[i][k] * L[j][k];
                }

                if (i == j) {
                    val = matris[i][i] - toplam;
                    if (val <= 0.0) {
                        flag = 0;
                    } else {
                        L[i][j] = sqrt(val);
                    }
                } else {
                    if (L[j][j] == 0.0) {
                        flag = 0;
                    } else {
                        L[i][j] = (matris[i][j] - toplam) / L[j][j];
                    }
                }
            }
        }

    if (!flag) {
            printf("HATA: Matris pozitif tanımlı değil, Cholesky ayrıştırması yapılamaz.\n");
        } else {
            printf("Cholesky alt üçgen matrisi L:\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    printf("%.4f ", L[i][j]);
                printf("\n");
            }
        }
    freeMatrix(matris, n);
    freeMatrix(L, n);
}
void SayisalTurev(float x,char* postfix,char* logbases){
    float h1,h,h2,turevhesabi = 0.0;
    int sayturevops;
    printf("Sayisal Türev\n");
    printf("İleri Fark ile Türev İçin-1\nGeri Fark ile Türev için-2\nMerkezi Fark ile Türev için-3\nBasınız...");
    scanf("%d",&sayturevops);
    printf("\nHangi noktada türev hesaplayacaksınız giriniz : \n");
    scanf("%f",&x);
    switch (sayturevops)
    {
    case 1:
        printf("İleri Fark\n");
        printf("dx giriniz : ");
        scanf("%f",&h);
        turevhesabi = (EvaluatePostfix(x+h,postfix,logbases)-EvaluatePostfix(x,postfix,logbases)) / h;
        break;
    case 2:
        printf("Geri Fark\n");
        printf("dx giriniz : ");
        scanf("%f",&h);
        turevhesabi = (EvaluatePostfix(x,postfix,logbases)-EvaluatePostfix(x-h,postfix,logbases)) / h;
        break;
    case 3:
        printf("Merkezi Fark\n");
        printf("dx giriniz : ");
        scanf("%f",&h);
        h1 = x + h;
        h2 = x - h;
        turevhesabi = (EvaluatePostfix(h1,postfix,logbases)-EvaluatePostfix(h2,postfix,logbases)) / (h*2);
        break;
    default:
        printf("Hatalı bir seçim");
        break;
    }
    printf("\nTürev değeriniz : %f\n",turevhesabi);
}

void GauusSeidel(void){
    int satir,sutun,i,j,maxIndex;
    printf("Gauus Seidel İterasyonu\n");
    do {
        printf("Lütfen bilinmeyen sayısını giriniz\n");
        scanf("%d",&sutun);
        printf("Lütfen denklem sayısını giriniz\n");
        scanf("%d",&satir);
        if (satir != sutun) {
                printf("Gauss-Seidel yöntemi için denklem sayısı ve bilinmeyen sayısı eşit olmalıdır. Lütfen tekrar deneyiniz.\n");
            }
    } while (satir!=sutun);
    float **matris=allocateMatrix(satir, sutun);
    float *b=(float*)malloc(sizeof(float)*satir);
    float *sonuclar=(float*)malloc(sizeof(float)*satir);
    float *exsonuclar=(float*)malloc(sizeof(float)*satir);
    printf("Sırasıyla bilinmeyenlerin kat sayılarını giriniz\n");
    for (i=0; i<satir; i++) {
        for (j=0; j<sutun; j++) {
            printf("Matrisin [%d][%d].elemanını giriniz\n",i+1,j+1);
            scanf("%f",&matris[i][j]);
        }
    }
    printf("Lütfen AX=B şeklindeki denkleminizin B kısmını giriniz\n");
    for (i=0; i<satir; i++) {
        printf("%d.satırı giriniz\n",i+1);
        scanf("%f",&b[i]);
    }
    for (i=0; i<satir; i++) {
        maxIndex=i;
        for (j=i+1; j<satir; j++) {
            if (fabs(matris[j][i])>fabs(matris[maxIndex][i])) {
                maxIndex=j;
            }
        }
        if (maxIndex!=i) {
            float *tempRow=matris[i];
            matris[i]=matris[maxIndex];
            matris[maxIndex]=tempRow;
            
            float tempB=b[i];
            b[i]=b[maxIndex];
            b[maxIndex]=tempB;
        }
    }
    printf("Lütfen başlangıç değerlerini giriniz: ");
    for (i=0; i<satir; i++) {
        scanf("%f",&exsonuclar[i]);
    }

    float epsilon = 0.0001;
    int iterasyon = 0;
    int yakinsama = 0;

    while (iterasyon < 1000 && !yakinsama) {
        iterasyon++;
        for (i = 0; i < satir; i++) {
            sonuclar[i] = b[i];
            for (j = 0; j < sutun; j++) {
                if (i != j) {
                    sonuclar[i] -= matris[i][j] * exsonuclar[j];
                }
            }
            sonuclar[i] /= matris[i][i];
        }

        yakinsama = 1;
        for (i = 0; i < satir; i++) {
            if (fabs(sonuclar[i] - exsonuclar[i]) > epsilon) {
                yakinsama = 0;
                break;
            }
        }

     
        for (i = 0; i < satir; i++) {
            exsonuclar[i] = sonuclar[i];
        }
    }
    printf("\nGauss-Seidel iterasyon sonuçları:\n");
    for (i = 0; i < satir; i++) {
        printf("x%d = %.4f\n", i+1, sonuclar[i]);
    }
    for (i = 0; i < satir; i++) {
        free(matris[i]);
    }
    free(matris);
    free(b);
    free(sonuclar);
    free(exsonuclar);
}
void Simpson(float x, char* postfix, char *logbases){
    float a, b, integraldeger = 0, dx;
    int i, n, method;
    printf("Simpson Yöntemi Seçimi:\n");
    printf("1: Simpson 1/3 Yöntemi\n");
    printf("2: Simpson 3/8 Yöntemi\n");
    printf("Seçiminizi yapınız (1 veya 2): ");
    scanf("%d", &method);

    printf("Lütfen integralin alt ve üst sınırını giriniz\n");
    scanf("%f %f", &a, &b);
    printf("n değerini giriniz (alt aralık sayısı):\n");
    scanf("%d", &n);

    dx = (b - a) / n;

    if (method == 1) {
        for (i = 0; i < n; i++) {
            float x0 = a + i * dx;
            float x1 = a + (i + 0.5) * dx;
            float x2 = a + (i + 1) * dx;
            integraldeger += (dx / 6) * (EvaluatePostfix(x0, postfix, logbases) + 4 * EvaluatePostfix(x1, postfix, logbases) + EvaluatePostfix(x2, postfix, logbases));
        }
    }
    else if (method == 2) {
        for (i = 0; i <= n - 3; i += 3) {
            float x0 = a + i * dx;
            float x1 = a + (i + 1) * dx;
            float x2 = a + (i + 2) * dx;
            float x3 = a + (i + 3) * dx;
            integraldeger += (3 * dx / 8) * (EvaluatePostfix(x0, postfix, logbases)+3 * EvaluatePostfix(x1, postfix, logbases)+ 3 * EvaluatePostfix(x2, postfix, logbases)+ EvaluatePostfix(x3, postfix, logbases));
        }
    }
    else {
        printf("Geçersiz seçim yaptınız.\n");
        return;
    }

    printf("İntegral Değeriniz : %f\n", fabs(integraldeger));
}
void Trapez(float x,char *postfix,char *logbases){
    float a,b,integraldeger=0,dx,x0,x1;
    int i,n;
    printf("Trapez Yöntemi\n");
    printf("lütfen integralin alt ve üst sınırını giriniz\n");
    scanf("%f %f",&a,&b);
    printf("n değerini giriniz\n");
    scanf("%d",&n);
    dx=(b-a)/n;
    x0=a;
    for (i=0; i<n; i++) {
        x1=x0+dx;
        integraldeger += ((x1 - x0) * (EvaluatePostfix(x0, postfix, logbases) + EvaluatePostfix(x1, postfix, logbases))) / 2;
        x0 = x1;
    }
    printf("İntegralin Değeri : %f",fabs(integraldeger));
}
void GregoryNewton(void){
    int xsayisi, i, j;
    printf("\nGregory Newton Enterpolasyonu\n");
    printf("Lütfen kaç tane x değerini olduğunu yazınız:");
    scanf("%d", &xsayisi);
    float *xler = (float *)malloc(sizeof(float) * xsayisi);
    float *yler = (float *)malloc(sizeof(float) * xsayisi);
    float **ilerifarklar = allocateMatrix(xsayisi, xsayisi);

    for(i=0;i<xsayisi;i++){
        xler[i] = i;
    }
    for(i=0;i<xsayisi;i++){
        printf("%d.y i  giriniz ",i);
        scanf("%f",&yler[i]);
    }
    for (i = 0; i < xsayisi; i++) {
        ilerifarklar[i][0] = yler[i];
    }
    for (j = 1; j < xsayisi; j++) {
        for (i = 0; i < xsayisi - j; i++) {
            ilerifarklar[i][j] = ilerifarklar[i + 1][j - 1] - ilerifarklar[i][j - 1];
        }
    }
    printf("\nIleri Farklar:\n");
    for (i = 0; i < xsayisi; i++) {
        printf("f[%d]: ", i);
        for (j = 0; j < xsayisi - i; j++) {
            printf("%-8.4f\t", ilerifarklar[i][j]);
        }
        printf("\n");
    }
    float x;
    printf("\nİnterpolasyon için x değerini giriniz: ");
    scanf("%f", &x);

  
    float result = yler[0];
    float term = 1;
    for (i = 1; i < xsayisi; i++) {
        term *= (x - xler[i - 1]) / (i);
        result += term * ilerifarklar[0][i];
    }

    printf("\nf(%.2f) ≈ %.2f\n", x, result);
}
int main(void){
    int temp=1;
    char ana_menu;
    char *logbases;
    char *metin;
    char *postfix;
    float x = 0.0;
    printf("-----Sayısal Analiz Yöntemleri Ekranına Hoş Geldiniz-----\n");
    printf("------------------BAZI ÖNEMLİ DETAYLAR-------------------\n");
    printf("*Fonksiyonunuzda negatif bir sayı varsa (0-sayı) şeklinde girebilirsiniz\n");
    printf("Desteklenen Trigonometrik İfadeler Sin Cos Tan ve tersleridir diğer trigonometrik ifadeleri lütfen bu ifadeler cinsinden yazınız.\n");
    printf("Aşağıdaki işlemlerden birini numarasını yazarak seçebilirsiniz\n");
    printf("0-Bisection\n1-Regula Falsi\n2-Newton-Raphson\n3-NxN'lik matrisin Tersi\n4-Cholesky Yöntemi\n5-Gauss Seidal\n6-Sayısal Türev\n7-Simpson\n8-Trapez\n9-Değişken Dönüşümsüz Gregory Newton");
    printf("Çıkış Yapmak için q tuşuna basmanız yeterli\n");
    printf("Lütfen 0-9 arasında bir sayı seçiniz çıkış yapmak için q basabilirsiniz\n");
    scanf(" %c",&ana_menu);
    switch (ana_menu) {
        case '0':
            system("clear");
            printf("\n\t\t\tBisection yöntemi\t\t\t\n");
            metin=(char*)malloc(sizeof(char)*100);
            postfix=(char*)malloc(sizeof(char)*100);
            logbases=(char*)malloc(sizeof(char)*100);
            printf("Bisection metodununda kullanmak istediğiniz denklemi giriniz\n");
            scanf("%s",metin);
            printf("Girmiş olduğunuz denklem %s",metin);
            InfixToPostfix(metin, postfix, logbases);
            BiSection(postfix, logbases);
            free(metin);
            free(postfix);
            free(logbases);
            break;
        case '1':
            system("clear");
            printf("\n\t\t\tRegula-Falsi yöntemi\t\t\t\n");
            metin=(char*)malloc(sizeof(char)*100);
            postfix=(char*)malloc(sizeof(char)*100);
            logbases=(char*)malloc(sizeof(char)*100);
            printf("Regula-Falsi yönteminde kullanmak istediğiniz denklemi giriniz\n");
            scanf("%s",metin);
            printf("Girmiş olduğunuz denklem %s",metin);
            InfixToPostfix(metin, postfix, logbases);
            RegulaFalsi(x, postfix, logbases);
            free(metin);
            free(postfix);
            free(logbases);
            break;
        case '2':
            system("clear");
            printf("\n\t\t\tNewton Raphson Yöntemi\t\t\t\n");
            metin=(char*)malloc(sizeof(char)*100);
            postfix=(char*)malloc(sizeof(char)*100);
            logbases=(char*)malloc(sizeof(char)*100);
            printf("Newton Raphson yönteminde kullanmak istediğiniz denklemi giriniz\n");
            scanf("%s",metin);
            printf("Girmiş olduğunuz denklem %s",metin);
            InfixToPostfix(metin, postfix, logbases);
            NewtonRaphson(x, postfix, logbases);
            free(metin);
            free(logbases);
            free(postfix);
            break;
        case '3':
            system("clear");
            printf("\n\t\t\tNxN'lik Matrisin Tersi\t\t\t\n");
            TersMatris();
            break;
        case '4':
            system("clear");
            printf("\n\t\t\t Cholesky (ALU ) Yöntemi \t\t\t\n");
            CholeskyYontemi();
            break;
        case '5':
            system("clear");
            printf("\n\t\t\tGauss Seidal\t\t\t\n");
            GauusSeidel();
            
            break;
        case '6':
            system("clear");
            printf("\n\t\t\tSayısal Turev\t\t\t\n");
            metin = (char*)malloc(sizeof(char)*100);
            postfix = (char*)malloc(sizeof(char) * 100);
            logbases = (char*)malloc(sizeof(char)*10);
            printf("Sayısal Türev yöntemin kullanmak istediğiniz denklemi giriniz : ");
            scanf("%s",metin);
            printf("Girmiş Olduğunuz Denklem :%s",metin);
            InfixToPostfix(metin, postfix, logbases);
            SayisalTurev(x, postfix, logbases);
            free(metin);
            free(logbases);
            free(postfix);
            
            break;
        case '7':
            system("clear");
            printf("\n\t\t\tSimpson \t\t\t\n");
            metin = (char*)malloc(sizeof(char)*100);
            postfix = (char*)malloc(sizeof(char) * 100);
            logbases = (char*)malloc(sizeof(char)*10);
            printf("Simpson Yönteminde kullanmak istediiniz denklemi giriniz : ");
            scanf("%s",metin);
            printf("Girmiş Olduğunuz Denklem :%s",metin);
            InfixToPostfix(metin, postfix, logbases);
            Simpson(x, postfix, logbases);
            free(metin);
            free(logbases);
            free(postfix);
            break;
        case '8':
            system("clear");
            printf("\n\t\t\tTrapez Yöntemi\t\t\t\n");
            metin=(char*)malloc(sizeof(char)*100);
            postfix=(char*)malloc(sizeof(char)*100);
            logbases=(char*)malloc(sizeof(char)*100);
            printf("Trapez Yönteminde kullanmak istediğiniz denklemi giriniz\n");
            scanf("%s",metin);
            printf("Girmiş olduğunuz denklem %s\n",metin);
            InfixToPostfix(metin, postfix, logbases);
            Trapez(x, postfix, logbases);
            free(metin);
            free(logbases);
            free(postfix);
            break;
        case '9':
            system("clear");
            printf("\n\t\t\tDeeğişken Dönüşümsüz Gregory Newton\t\t\t\n");
            GregoryNewton();
            break;
        case 'q':
            system("clear");
            printf("\nÇıkış yapılıyor...");
            exit(1);
            break;
        default:
            printf("Geçersiz giriş! Lütfen 0-9 arasında bir sayı ya da 'q' giriniz.\n");
            break;
    }
    return 0;
}
