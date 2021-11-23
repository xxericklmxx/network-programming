#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
void imprimir(int *a){

    for (int i = 0; i < 4; i++)
    {
        printf("%d.",a[i]);
    }
    printf("\n\n");
}

int digito(char n){
 
     switch ((int)n)
       {
       case 48:
           return 0;
           break;
           case 49:
           return 1;
           break;
           case 50:
           return 2;
           break;
           case 51:
           return 3;
           break;
            case 52:
           return 4;
           break;
            case 53:
           return 5;
           break;
            case 54:
           return 6;
           break;
            case 55:
           return 7;
           break;
            case 56:
           return 8;
           break;
           case 57:
           return 9;
           break;       
       default:
       return -1;
           break;
       }
       
}
int convertir_numero(char *num)
{
    int numero=0;
for (int i = 0; i < 3; i++)
{
    if(digito(num[i])!=-1 ){
       
      numero=numero*10+digito(num[i]);
      
    }
}
return numero;
}

int *convertir_entero(char *ip_add){
char octeto[3];
int *ip=(int *)(malloc(4*sizeof(int)));
 int n=0,k=0;

for ( int i = 0; i < 15; i=k)
{
for (int  j= 0; j < 4; j++)
{   k++;
    if(ip_add[i+j]=='.' || k>14 || ip_add[i+j]==0 )
    {
     break;      
    }else{
     octeto[j]=ip_add[i+j];
  
    
       }
}
if(k>14){
    break;
}
if(n<4)
{
   ip[n]=convertir_numero(octeto);
memset(&octeto,0,3);
}

n++; 
}
   
//imprimir(ip);
return ip;
}

 int *get_mascara(int mask){ 
 int *ip_mask =(int *)(malloc(4*sizeof(int)));
 
 int octetos1,bits_1,numero=0;
octetos1=mask/8;
bits_1=mask%8;

for (int i = 0; i < octetos1; i++)
{
    ip_mask[i]=255;
}

for (int i = 0; i < bits_1; i++)
{
    numero=numero+( int)pow(2,8-(i+1));
    
}
if(mask!=32)
{ip_mask[octetos1]=numero;
}
/*  printf(" %d. ",ip_mask[0]);
printf(" %d. ",ip_mask[1]);
printf(" %d. ",ip_mask[2]);
printf(" %d. ",ip_mask[3]); 
 */
return ip_mask;
}



void get_broadcast_address(char *ip_add,int mask,char *output_buffer){

int *ip_addentero=convertir_entero(ip_add);
 int *mascara=get_mascara(mask);
 int *mask2=get_mascara(32);
int ip_red[4],complemento_mask[4],broadcast_entero[4];
int n =0;

for (int i = 0; i < 4; i++)
{
    ip_red[i]=ip_addentero[i] & mascara[i];
    complemento_mask[i]= mascara[i] ^ mask2[i]; 
    broadcast_entero[i]=ip_red[i] | complemento_mask[i];
}
for (int i = 0; i < 4; i++)
{
    n+=sprintf(&output_buffer[n],"%d",broadcast_entero[i]);
    output_buffer[n]='.';
    n++;
    
}
free(mascara);
free(mask2);
free(ip_addentero);

 



}

unsigned int get_ip_integeral_equivalent(char *ip_addr){

unsigned int *ip_addentero=convertir_entero(ip_addr);
unsigned int ip_entero=0x00000000;

ip_entero=ip_addentero[0]<<24 | ip_addentero[1]<<16 | ip_addentero[2]<<8 | ip_addentero[3] ;


return ip_entero;


}


void get_abcd_ip_format(unsigned int ip_addr, char *output_buffer){
    int n=0;

    n+=sprintf(&output_buffer[n],"%u.%u.%u.%u",ip_addr>>24,(ip_addr>>16 & 0x000000ff),(ip_addr>>8 & 0x000000ff),ip_addr & 0x000000ff);
    

}

void get_network_id(char *ip_addr, char mask, char *output_buffer){
 int n=0;
  int *ip_addentero=convertir_entero(ip_addr);
  int *mascara=get_mascara(mask);
  
  n+=sprintf(&output_buffer[n],"%u.%u.%u.%u",(ip_addentero[0] & mascara[0]),(ip_addentero[1] & mascara[1]),(ip_addentero[2] & mascara[2]),(ip_addentero[3] & mascara[3]));

}

unsigned int get_subnet_cardinality(char mask)
{
    return pow(2,(32-mask))-2;
}


int check_ip_subnet_membership(char *network_id, char mask, char *check_ip){
    int n=0;
    unsigned int red_entero= get_ip_integeral_equivalent(network_id);
    unsigned int *mascara_nuevo=get_mascara(mask);  
    char masca[15];
    n+=sprintf(&masca[n],"%u.%u.%u.%u",mascara_nuevo[0],mascara_nuevo[1],mascara_nuevo[2],mascara_nuevo[3]); 
    unsigned int mascara_entero=get_ip_integeral_equivalent(masca);
    unsigned int ip_nuevo=get_ip_integeral_equivalent(check_ip);
    unsigned int respuesta=0x00000000;
    respuesta=ip_nuevo & mascara_entero;
 //   printf("red %u mascara %u nuevo ip %u , la respuesta es %u",red_entero,mascara_entero,ip_nuevo,respuesta);
    if(respuesta==red_entero)
    {
        return 0;
    }
    else{
        return-1;
    }


}


int main( int argc, char *argv[]){
  /*   int mask;
    char ip_addr[15]; 
    char ipadd_buffer[15];   
    memset(ip_addr,0,15);
    memset(ipadd_buffer,0,15);
    printf("ingrese la mascara : ");
    scanf("%d",&mask);    
    printf("ingrese la direccion ip : ");
    scanf("%s",ip_addr);      
    printf("\n%s \n",ip_addr);
   get_broadcast_address(ip_addr,mask,ipadd_buffer);
    printf("broadcast addres = %s\n",ipadd_buffer);
 */

    //pregunta 2
  /*   unsigned int int_ip =get_ip_integeral_equivalent(ip_addr);
    printf("integer equivalent for %s is %u",ip_addr,int_ip);
    */ 

    //pregunta 3

 /*   get_abcd_ip_format(int_ip,ipadd_buffer);
    printf(" \n ip in A.B.C.D format is = %s\n",ipadd_buffer);
 */

    //pregunta 4
  /*   get_network_id(ip_addr,mask,ipadd_buffer);
    printf("network id = %s \n",ipadd_buffer);
 */
    //pregunta 5
/* 
    unsigned char mask1=mask;
    printf("subnet cardinality for mask = %u is %u \n",mask1,get_subnet_cardinality(mask1));
 */
    //pregunta 6
    unsigned char mask1;
    char network_id[15],nueva_ip[15];
    printf("ingrese la nueva direccion de red : \n");
    scanf("%s",&network_id);
    printf("ingrese la mascara de la red : \n");
    scanf("%u",&mask1);
    printf("ingrese la direccion ip a verificar: \n");
    scanf("%s",&nueva_ip);

   // printf("%s\n",network_id);
   // printf("%s\n",nueva_ip);
    int result = check_ip_subnet_membership(network_id,mask1,nueva_ip);
    if(result==0)
    {
        printf("ip Address = %s is a member of subnet %s/%u\n",nueva_ip,network_id,mask1);
    }else{
        printf("ip Address = %s is a not member of subnet %s/%u\n",nueva_ip,network_id,mask1);
    }
    

}