#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



 struct Arac {
     char plaka[20];
     time_t girisZamani;
     struct Arac *next;
 };

 struct Arac *head =NULL;

 int kapasite = 10;
 int mevcutArac =0;
 float gunlukKazanc = 0;


 void menu();
 void aracGrisi();
 void aracCikisi();
 void plakayaGoreArama();
 void aracListele();
 float ucretHesapla(time_t giris,time_t cikis);

 int main(){
     int secim;

     do{
        menu();
        scanf("%d", &secim);

        while (getchar() != '\n');

        switch (secim) {
    case 1:
        aracGrisi();
        break;
    case 2:
        aracCikisi();
        break;
    case 3:
        aracListele();
        break;
    case 4:
        plakayaGoreArama();
        break;
    case 5:
        printf("Gunluk Kazanc: %f TL \n",gunlukKazanc);
        break;
    case 0:
        printf("Programdan Cıkılıyor \n");
        break;
    default:
        printf("Hatalı Secim \n");
        }
     } while (secim !=0);
     return 0;
 }

 void menu() {
     printf("\n -----OTOPARK YONETIMI---- \n");
     printf("1-Arac Girisi \n");
     printf("2-Arac Cikisi \n");
     printf("3-Araclari Listele \n");
     printf("4-Plakaya Gore Ara \n");
     printf("5-Gunluk Kazanc \n");
     printf("0-Cikis \n");
     printf("Seciminiz: ");

 }

 void aracGrisi() {
     if(mevcutArac >= kapasite){
        printf("Otopark dolu. Giriş yapılamaz \n");
        return ;
     }

     char plaka[20];
     printf("Plaka Giriniz: ");
     scanf(" %[^\n]s", plaka);

     struct Arac *temp = head;

     while(temp!=NULL){
        if (strcmp(temp -> plaka,plaka)==0){
            printf("Bu plaka zaten otoparkta \n");
            return;
        }
        temp = temp ->next;
     }

     struct Arac *temp2 = (struct Arac *)malloc(sizeof(struct Arac));

     strcpy(temp2 ->plaka, plaka);
     time(&temp2 -> girisZamani);
     temp2 ->next =NULL;

     if(head == NULL)
        head = temp2;

     else{
        temp = head;
        while(temp->next !=NULL)
            temp = temp->next;
        temp->next=temp2;
     }
     mevcutArac++;
     printf("Arac otoparka giris yapti \n");
 }


 void aracCikisi(){
     if(head == NULL){
        printf("Otopark Bos \n");
        return;
     }

     char plaka[20];
     printf("Aracın plakasını giriniz: ");
     scanf(" %[^\n]s",plaka);

     struct Arac *temp =head;
     struct Arac *prev = NULL;

     while (temp != NULL && strcmp(temp->plaka,plaka)!=0) {
        prev = temp;
        temp = temp ->next;
     }

     if (temp == NULL) {
        printf("Arac bulunamadi \n");
        return;
     }

     time_t cikisZamani;
     time(&cikisZamani);

     float ucret = ucretHesapla(temp->girisZamani,cikisZamani);
     gunlukKazanc += ucret;

     if(prev == NULL)
        head = temp ->next;
     else
        prev ->next = temp ->next;

     free(temp);
     mevcutArac--;

     printf("Arac cikisi yapildi. Odenecek ucret: %f  TL \n",ucret);
 }

 void aracListele(){
     if(head == NULL){
        printf("Otopark Bos \n ");
        return;
     }

     struct Arac *temp = head;
     int sira=1;

     printf("\n  Otoparktaki Araclar: \n");
     while(temp != NULL){
        printf("%d. sira: %s \n", sira,temp->plaka);
        temp = temp->next;
        sira++;
     }
 }


 void plakayaGoreArama(){
     if(head == NULL) {
        printf("Otopark bos \n");
        return;
     }

     char plaka[20];
     printf("Aranacak Plaka: ");
     scanf(" %[^\n]s",plaka);

     struct Arac *temp = head;
     int sira=1;

     while(temp!=NULL){
        if(strcmp(temp->plaka,plaka)==0){
            printf(" %s plakali arac otoparktadır. \n",plaka);
            printf("Park Sirasi: %d \n",sira);
            return;
        }

        temp = temp -> next;
        sira++;
     }

     printf("Arac bulunamadi \n");
 }

 float ucretHesapla(time_t giris, time_t cikis){
     double dakika =difftime(cikis, giris) /60;

     if(dakika <= 60)
        return 50;
     else
        return 50 + ((dakika -60)/60) *25 ; }


