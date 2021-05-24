//------------2020/2021 VER� YAPILARI �DEV 2 (YI�IN)------------//
//---------------------�EYDA ASLI KO�Y���T----------------------//
//--------------------------171220028---------------------------//

#include <stdio.h>
#include <stdlib.h>
 
int secim;
 
//d���mlerimizi tutaca��m�z struct yap�s�
struct Stack{
    int sayi;
    struct Stack *sonraki;
};
 
//Stack yap�lar� i�in en �st ve gecici olu�turuyoruz
struct Stack* enUst_islem = NULL;
struct Stack* enUst_geri = NULL;
struct Stack* gecici_islem;
struct Stack* gecici_geri;

//Eklenecek girdiler i�in d���m olu�turuyoruz
struct Stack* dugumOlustur()
{
    struct Stack* yeniKayit = (struct Stack*)malloc(sizeof(struct Stack));
    return yeniKayit;
}
 
void EKLE(int sayi) //�slem stack ine ekleme yapmak i�in kulland���m�z fonksiyon
{
    struct Stack* eklenecek = dugumOlustur();
    eklenecek->sayi = sayi;
    gecici_islem = enUst_islem;
    eklenecek->sonraki = gecici_islem;
    enUst_islem = eklenecek;
}

void geriyeEKLE(int sayi){ //Geri stack ine ekleme yapmak i�in kulland���m�z fonksiyon
	struct Stack* eklenecek = dugumOlustur();
    eklenecek->sayi = sayi;
    gecici_geri = enUst_geri;
    eklenecek->sonraki = gecici_geri;
    enUst_geri = eklenecek;
}

void SIL() //�slem stack inden silme yapmak i�in kulland���m�z fonksiyon. �slemden silinen veri geri i�erisine ekleniyor
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

void GERI_AL() //Yap�lan i�lemi geri almak i�in kulland���m�z fonksiyon.
{
    if(enUst_geri != NULL) //Geri bo� de�ilse i�erisindekileri i�lem i�erisine ekliyoruz
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
    else  //Geri bo� ise i�lem i�erisinden geri alma yap�yoruz
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

//�slemin i�erisindekileri ekrana yazmak i�in kulland���m�z fonksiyon
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

void secimYap(int secim)  //Men�de yapt���m�z tercihleri switch case ile �al��t�r�yoruz
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
