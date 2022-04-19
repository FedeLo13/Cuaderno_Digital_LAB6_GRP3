#include "horario.h"
#include "funciones_clave.c"

int main(){
    int n;
    carga_horarios();
    crea_horarios();
    modifica_horarios();
    elimina_horarios();
    lista_horarios();
    return 0;
}
void carga_horarios(){

    int cont=0,i,j,semaforo;
    char temp[100],*aux;
    const char s[2] = "-";
    FILE *f;
    f = fopen("horarios.txt","r");
    if(f == NULL){
        printf("Error al abrir el fichero.\n");
    }

    while(!feof(f)){
        fgets(temp,100,f);
        cont++;
    }

    rewind(f);
    v_horarios = (horarios*)malloc(cont*sizeof(horarios));
    if(v_horarios == NULL){
        printf("No se ha podido reservar la memoria.\n");
    }
    for(i=0;i<cont;i++){
        j=1;
        vaciar(temp,100);
        fgets(temp,100,f);
        aux = strtok(temp,s);
        while(aux != NULL){
            switch (j){
                case 1:
                    strcpy(v_horarios[i].Id_profesor,aux);
                    break;
                case 2:
                    strcpy(v_horarios[i].Dia_clase,aux);
                    break;
                case 3:
                    strcpy(v_horarios[i].Hora_clase,aux);
                    break;
                case 4:
                    strcpy(v_horarios[i].Id_materia,aux);
                    break;
                case 5:
                    strcpy(v_horarios[i].Grupo,aux);
                    break;
            }
            aux = strtok(NULL,s);
            j++;
        }
    }
    fclose(f);
}

void lista_horarios(){
    int cont=0,i;
    char temp[100];
    FILE *f;
    f = fopen("horarios.txt","r");
    if(f == NULL){
        printf("Error al abrir el fichero.\n");
    }

    while(!feof(f)){
        fgets(temp,100,f);
        cont++;
    }
    for(i=0;i<cont;i++){
        printf("%i. %s-%s-%s-%s-%s\n",i+1,v_horarios[i].Id_profesor,v_horarios[i].Dia_clase,v_horarios[i].Hora_clase,v_horarios[i].Id_materia,v_horarios[i].Grupo);
    }
    fclose(f);
}

void modifica_usuarios(){
    int cont=0,n;
    char temp[100],c,aux[100];
    lista_usuarios();
    FILE *f;
    f = fopen("usuarios.txt","r");
    if(f == NULL){
        printf("Error al abrir el fichero.\n");
    }

    while(!feof(f)){
        fgets(temp,100,f);
        cont++;
    }

    do{
        printf("Introduce el numero correspondiente al usuario que desea editar\n");
        scanf("%i",&n);
        fflush(stdin);
    }while(n<=0 || n>cont);
    n--;
    do{
        printf("Escriba el nuevo identificador del usuario (maximo 3 digitos), o escriba x si no quiere editarlo\n");
        gets(aux);
        fflush(stdin);
        if(strcmp(aux,"x")!=0){
            strcpy(v_usuarios[n].Id_usuario,aux);
        }
    }while(strlen(v_usuarios[n].Id_usuario) > 3);
    do{
        printf("Escriba el nuevo nombre (maximo 20 caracteres), o escriba x si no quiere editarlo\n");
        gets(aux);
        fflush(stdin);
        if(strcmp(aux,"x")!=0){
            strcpy(v_usuarios[n].Nomb_usuario,aux);
        }
    }while(strlen(v_usuarios[n].Nomb_usuario) > 20);
    do{
        printf("Escriba el nuevo nombre de usuario(maximo 5 caracteres), o escriba x si no quiere editarlo\n");
        gets(aux);
        fflush(stdin);
        if(strcmp(aux,"x")!=0){
            strcpy(v_usuarios[n].Usuario,aux);
        }
    }while(strlen(v_usuarios[n].Usuario) > 5);
    do{
        printf("Escriba la nueva contrase�a(maximo 8 caracteres), o escriba x si no quiere editarlo\n");
        gets(aux);
        fflush(stdin);
        if(strcmp(aux,"x")!=0){
            strcpy(v_usuarios[n].Contrasena,aux);
        }
    }while(strlen(v_usuarios[n].Contrasena) > 8);
    do{
    printf("Esta seguro/a de que quiere realizar estos cambios? (s/n)\n");
    scanf("%c",&c);
    fflush(stdin);
    if(c == 'n'){
        vaciar(v_usuarios[n].Id_usuario,strlen(v_usuarios[n].Id_usuario));
        vaciar(v_usuarios[n].Nomb_usuario,strlen(v_usuarios[n].Nomb_usuario));
        vaciar(v_usuarios[n].Perfil_usuario,strlen(v_usuarios[n].Perfil_usuario));
        vaciar(v_usuarios[n].Usuario,strlen(v_usuarios[n].Usuario));
        vaciar(v_usuarios[n].Contrasena,strlen(v_usuarios[n].Contrasena));
    }
    }while(c != 'n' && c!='s');
    fclose(f);
}


void crea_usuarios(){
    int n,cont=0,i,v=1;
    char c,temp[100];
    FILE *f;
    f = fopen("usuarios.txt","r");
    if(f == NULL){
        printf("Error al abrir el fichero.\n");
    }

    while(!feof(f)){
        fgets(temp,100,f);
        cont++;
    }
    i=cont;
    cont++;
    v_usuarios=(Usuario*)realloc(v_usuarios,cont*sizeof(Usuario));
    do{
        printf("Introduzca 1 para crear un profesor, 2 para crear un administrador\n");
        scanf("%i",&n);
        fflush(stdin);
        if(n==1){
            char prof[]={'p','r','o','f','e','s','o','r','\0'};
            strcpy(v_usuarios[i].Perfil_usuario,prof);
        }
        else{
            if(n==2){
                char adm[]= {'a','d','m','i','n','i','s','t','r','a','d','o','r','\0'};
                strcpy(v_usuarios[i].Perfil_usuario,adm);
            }
        }
    }while(n != 1 && n != 2);
    do{
        printf("Introduzca el identificador del %s (maximo 3 digitos)\n",v_usuarios[i].Perfil_usuario);
        gets(v_usuarios[i].Id_usuario);
        fflush(stdin);
    }while(strlen(v_usuarios[i].Id_usuario) > 3);
    do{
        printf("Introduzca el nombre del %s (maximo 20 caracteres)\n",v_usuarios[i].Perfil_usuario);
        gets(v_usuarios[i].Nomb_usuario);
        fflush(stdin);
    }while(strlen(v_usuarios[i].Nomb_usuario) > 20);
    do{
        printf("Introduzca el nombre de usuario del %s (maximo 5 caracteres)\n",v_usuarios[i].Perfil_usuario);
        gets(v_usuarios[i].Usuario);
        fflush(stdin);
    }while(strlen(v_usuarios[i].Usuario) > 5);
    do{
        printf("Introduzca la contrasena del %s (maximo 8 caracteres)\n",v_usuarios[i].Perfil_usuario);
        gets(v_usuarios[i].Contrasena);
        fflush(stdin);
    }while(strlen(v_usuarios[i].Contrasena) > 8);
    do{
    printf("Esta seguro/a de que quiere realizar esta operacion? (s/n)\n");
    scanf("%c",&c);
    fflush(stdin);
    if(c == 'n'){
        vaciar(v_usuarios[i].Id_usuario,strlen(v_usuarios[i].Id_usuario));
        vaciar(v_usuarios[i].Nomb_usuario,strlen(v_usuarios[i].Nomb_usuario));
        vaciar(v_usuarios[i].Perfil_usuario,strlen(v_usuarios[i].Perfil_usuario));
        vaciar(v_usuarios[i].Usuario,strlen(v_usuarios[i].Usuario));
        vaciar(v_usuarios[i].Contrasena,strlen(v_usuarios[i].Contrasena));
        v_usuarios=(Usuario*)realloc(v_usuarios,i*sizeof(Usuario));
        v=0;
    }
    }while(c != 'n' && c!='s');
    fclose(f);
    vuelca_usuarios(v);
}

void elimina_usuarios(){
    int cont=0,n,i=0,admns=0,j,v=-1;
    char temp[100];
    lista_usuarios();
    FILE *f;
    f = fopen("usuarios.txt","r");
    if(f == NULL){
        printf("Error al abrir el fichero.\n");
    }

    while(!feof(f)){
        fgets(temp,100,f);
        cont++;
    }
    do{
        printf("Introduce el numero correspondiente al usuario que desea eliminar\n");
        scanf("%i",&n);
        fflush(stdin);
    }while(n<=0 || n>cont);
    n--;
    cont--;
    if (strcmp(v_usuarios[n].Perfil_usuario,"administrador") == 0){
        while(i<cont && admns < 2){
            if(strcmp(v_usuarios[i].Perfil_usuario,"administrador") == 0){
                admns++;
            }
            i++;
        }
    }
    if(admns == 1){
        printf("No se puede realizar esta accion debido a que solo existe 1 administrador\n");
        v=0;
    }
    else{
        vaciar(v_usuarios[n].Id_usuario,strlen(v_usuarios[n].Id_usuario));
        vaciar(v_usuarios[n].Nomb_usuario,strlen(v_usuarios[n].Nomb_usuario));
        vaciar(v_usuarios[n].Perfil_usuario,strlen(v_usuarios[n].Perfil_usuario));
        vaciar(v_usuarios[n].Usuario,strlen(v_usuarios[n].Usuario));
        vaciar(v_usuarios[n].Contrasena,strlen(v_usuarios[n].Contrasena));
        if(n<cont){
            for(j=n;j<cont;j++){
                strcpy(v_usuarios[j].Id_usuario,v_usuarios[j+1].Id_usuario);
                vaciar(v_usuarios[j+1].Id_usuario,strlen(v_usuarios[j+1].Id_usuario));
                strcpy(v_usuarios[j].Nomb_usuario,v_usuarios[j+1].Nomb_usuario);
                vaciar(v_usuarios[j+1].Nomb_usuario,strlen(v_usuarios[j+1].Nomb_usuario));
                strcpy(v_usuarios[j].Perfil_usuario,v_usuarios[j+1].Perfil_usuario);
                vaciar(v_usuarios[j+1].Perfil_usuario,strlen(v_usuarios[j+1].Perfil_usuario));
                strcpy(v_usuarios[j].Usuario,v_usuarios[j+1].Usuario);
                vaciar(v_usuarios[j+1].Usuario,strlen(v_usuarios[j+1].Usuario));
                strcpy(v_usuarios[j].Contrasena,v_usuarios[j+1].Contrasena);
                vaciar(v_usuarios[j+1].Contrasena,strlen(v_usuarios[j+1].Contrasena));
            }
            v_usuarios=(Usuario*)realloc(v_usuarios,cont*sizeof(Usuario));
         }
         else{
            v_usuarios=(Usuario*)realloc(v_usuarios,cont*sizeof(Usuario));
         }
    }
    fclose(f);
    vuelca_usuarios(v);
}

void vuelca_horario(int n){
    int cont=0,i;
    char temp[100];
    FILE *f;
    f = fopen("hoario.txt","r");
    if(f == NULL){
        printf("Error al abrir el fichero.\n");
    }

    while(!feof(f)){
        fgets(temp,100,f);
        cont++;
    }
    fclose(f);
    cont= cont + n;
    f = fopen("horario.txt","w");
    if(f == NULL){
      printf("Error al abrir el fichero.\n");
    }
    for(i=0;i<cont;i++){
        fprintf(f,"%s-%s-%s-%s-%s",v_horarios[i].Id_profesor,v_horario[i].Dia_clase,v_horario[i].Hora_clase,v_horario[i].Id_materia,v_horario[i].Grupo);
        if(i != (cont-1)){
            fprintf(f,"\n");
        }
    }
    fclose(f);
}
