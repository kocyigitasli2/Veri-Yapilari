//------------2020/2021 VERÝ YAPILARI ÖDEV 2 (YIÐIN)------------//
//---------------------ÞEYDA ASLI KOÇYÝÐÝT----------------------//
//--------------------------171220028---------------------------//

#include <stdio.h>
#include <stdlib.h>
 
int secim;
 
//düðümlerimizi tutacaðýmýz struct yapýsý
struct Stack{
    int sayi;
    struct Stack *sonraki;
};
 
//Stack yapýlarý için en üst ve gecici oluþturuyoruz
struct Stack* enUst_islem = NULL;
struct Stack* enUst_geri = NULL;
struct Stack* gecici_islem;
struct Stack* gecici_geri;

//Eklenecek girdiler için düðüm oluþturuyoruz
struct Stack* dugumOlustur()
{
    struct Stack* yeniKayit = (struct Stack*)malloc(sizeof(struct Stack));
    return yeniKayit;
}
 
void EKLE(int sayi) //Ýslem stack ine ekleme yapmak için kullandýðýmýz fonksiyon
{
    struct Stack* eklenecek = dugumOlustur();
    eklenecek->sayi = sayi;
    gecici_islem = enUst_islem;
    eklenecek->sonraki = gecici_islem;
    enUst_islem = eklenecek;
}

void geriyeEKLE(int sayi){ //Geri stack ine ekleme yapmak için kullandýðýmýz fonksiyon
	struct Stack* eklenecek = dugumOlustur();
    eklenecek->sayi = sayi;
    gecici_geri = enUst_geri;
    eklenecek->sonraki = gecici_geri;
    enUst_geri = eklenecek;
}

void SIL() //Ýslem stack inden silme yapmak için kullandýðýmýz fonksiyon. Ýslemden silinen veri geri içerisine ekleniyor
{
    if(enUst_islem != NULL)
    {
        if(enUst_islem->sonraki != NULL)
        {
            struct Stack* gecici_islem2 = enUst_islem;
            enUst_islem = enUst_islem->sonraki;
            geriyeEKLE(gecici_islem2->sayi);
            printf("%d SILINDI\n\n",gecici_islem2->sayi);
            free(gecici_islem2);
        }
        else
        {
        	printf("%d SILINDI\n\n",enUst_islem->sayi);
        	geriyeEKLE(enUst_islem->sayi);
            free(enUst_islem);
            enUst_islem = NULL;
        }
    }
    else
    {
        printf("\nSTACK BOS!!!\n\n");
    }
}

void GERI_AL() //Yapýlan iþlemi geri almak için kullandýðýmýz fonksiyon.
{
    if(enUst_geri != NULL) //Geri boþ deðilse içerisindekileri iþlem içerisine ekliyoruz
    {
        if(enUst_geri->sonraki != NULL)
        {
            struct Stack* gecici_geri2 = enUst_geri;
            enUst_geri = enUst_geri->sonraki;
            printf("%d SILME ISLEMI GERI ALINDI\n\n",gecici_geri2->sayi);
            EKLE(gecici_geri2->sayi);
            free(gecici_geri2);
        }
        else
        {
        	printf("%d SILME ISLEMI GERI ALINDI\n\n",enUst_geri->sayi);
        	EKLE(enUst_geri->sayi);
            free(enUst_geri);
            enUst_geri = NULL;
        }
    }
    else  //Geri boþ ise iþlem içerisinden geri alma yapýyoruz
    {
       if(enUst_islem != NULL)
    {
        if(enUst_islem->sonraki != NULL)
        {
            struct Stack* gecici_islem2 = enUst_islem;
            enUst_islem = enUst_islem->sonraki;
            printf("%d EKLEME ISLEMI GERI ALINDI\n\n",gecici_islem2->sayi);
            free(gecici_islem2);
        }
        else
        {
        	printf("%d EKLEME ISLEMI GERI ALINDI\n\n",enUst_islem->sayi);
            free(enUst_islem);
            enUst_islem = NULL;
        }
    }
    }
}

//Ýslemin içerisindekileri ekrana yazmak için kullandýðýmýz fonksiyon
void YAZDIR()
{
    if(enUst_islem == NULL)
    {
        printf("\n STACK BOS!!\n");
    }
    else
    {
        gecici_islem = enUst_islem;
        printf("\nEKRANA YAZILDI -> ");
        while(gecici_islem->sonraki != NULL)
        {
            printf("%d ", gecici_islem->sayi);
            gecici_islem = gecici_islem->sonraki;
        }
        printf("%d ", gecici_islem->sayi);
        printf("\n\n");
    }
 
}

void secimYap(int secim)  //Menüde yaptýðýmýz tercihleri switch case ile çalýþtýrýyoruz
{
    int sayi;
    switch(secim)
    {
        case 1:
            printf("Eklemek istediginiz sayiyi giriniz... ");
            scanf("%d", &sayi);
            EKLE(sayi);
            printf("%d EKLENDI\n\n",sayi);
            break;
        case 2:
            SIL();
            break;
        case 3:
        	GERI_AL();
        	break;
        case 4:
        	YAZDIR();
        	break;
        default:
        	printf("YANLIS GIRIS YAPILDI. LUTFEN 1 - 4 ARASI SECIM YAPINIZ!!!\n\n");
    }
}

int main()
{
     while(true)
    {
    	printf("|-------MENU-------|");
        printf("\n| 1>STACKE EKLE    |");
        printf("\n| 2>STACKTEN CIKAR |");
        printf("\n| 3>ISLEMI GERI AL |");
        printf("\n| 4>EKRANA YAZDIR  |");
        printf("\n|------------------|");
        printf("\nSECIMINIZ --> ");
        scanf("%d", &secim);
        secimYap(secim);
    }
}
