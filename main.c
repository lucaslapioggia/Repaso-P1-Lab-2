#include <stdio.h>
#include <stdlib.h>

/*
------------------LISTAS SIMPLES------------------
*/
typedef struct
{
  char patente[6];
  int valor;
  char marca[10];
}celdaAuto;
typedef struct
{
  celdaAuto dato;
  struct nodoAuto*siguiente;
}nodoAuto;
nodo*inicLista()
{
    return NULL;
}
nodo*crearNodo(celdaAuto dato)
{
    nodo*aux=(nodo*)malloc(sizeof(nodo));
    aux->dato=dato;
    aux->siguiente=NULL;
    return aux;
}
nodo*AgregaralPpio(nodo*lista,nodo*nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente=lista;
        lista=nuevoNodo;
    }
    return lista;
}
nodo*BuscarUltimo(nodo*lista)
{
    nodo*seg=lista;
    if(seg!=NULL)
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
    }
    return seg;
}
nodo*BuscarNodo(nodo*lista,char patente[])//main patente[7]
{
    nodo*seg=lista;
    while(seg!=NULL&&strcmp(patente,seg->dato.patente)!=0)
    {
        seg=seg->siguiente;
    }
    return seg;
}
nodo*AgregarAlFinal(nodo*lista,nodo*nuevoNodo)
{
    if(lista==NULL)
    {
       lista=nuevoNodo;
    }
    else
    {
        nodo*ultimo=BuscarUltimo(lista);
        ultimo->siguiente=nuevoNodo;
    }
    return lista;
}
nodo*BorrarNodo(nodo*lista,char patente[])
{
    nodo*ante;
    nodo*seg;
    if(lista!=NULL&&strcmp(patente,lista->dato.patente)==0)
    {
        nodo*aux=lista;
        lista=lista->siguiente;
        free(aux);
    }
    else
    {
        seg=lista;
        while(seg!=NULL&&strcmp(patente,seg->dato.patente)!=0)
        {
            ante=seg;
            seg=seg->siguiente;
        }
        if(seg!=NULL)
        {
            ante->siguiente=seg->siguiente;
            free(seg);
        }
    }
    return lista;
}
nodo*AgregarNodoManteniedoOrden(nodo*lista,nodo*nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
      if(strcmp(nuevoNodo->dato.patente,lista->dato.patente)<0)
      {
          lista=AgregaralPpio(lista,nuevoNodo);
      }
      else
      {
         nodo*ante=lista;
         nodo*seg=lista->siguiente;
         while(seg!=NULL&&(strcmp(nuevoNodo->dato.patente,seg->dato.patente)>0))
         {
             ante=seg;
             seg=seg->siguiente;
         }
         nuevoNodo->siguiente=seg;
         ante->siguiente=nuevoNodo;
      }
    }
    return lista;
}
void MuestraNodo(celdaAuto dato)
{
    printf("\n Patente : %s ",dato.patente);
    printf("\n Valor   : %i ",dato.valor);
    printf("\n Marca   : %s ",dato.marca);
}
void RecorreMuestraLista(nodo*lista)
{
    nodo*seg=lista;
    while(seg!=NULL)
    {
        MuestraNodo(seg->dato);
        seg=seg->siguiente;
    }
}

/*
------------------LISTAS DOBLES------------------
*/
typedef struct
{
    int dato;
    struct nodo2 * ste;
    struct nodo2 * ante;
} nodo2;
nodo2 * inicLista()
{
    return NULL;
}
nodo2 * crearNodo(int dato)
{
    nodo2* aux= (nodo2 *)malloc(sizeof(nodo2));
    aux->dato=dato;
    aux->ante=NULL;
    aux->ste=NULL;
    return aux;
}
nodo2 * agregarAlPrincipio(nodo2 * lista, nodo2 * nuevoNodo)
{
    nuevoNodo->ste=lista;
    if(lista!=NULL)
    {
        lista->ante=nuevoNodo;
    }
    return nuevoNodo;
}
nodo2 * buscarUltimoR(nodo2 * lista)// recursivo
{
    nodo2 * rta=NULL;
    if(lista!=NULL)
    {
        if(lista->ste==NULL)
        {
            rta=lista;
        }
        else
        {
            rta=buscarUltimoR(lista->ste);
        }
    }
    return rta;
}
nodo2 * agregarAlFinal(nodo2 * lista, nodo2 * nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nodo2 * ultimo = buscarUltimoR(lista);
        ultimo->ste = nuevoNodo;

        nuevoNodo->ante = ultimo;
    }
    return lista;
}
nodo2 * insertarNodo(nodo2 * lista, nodo2 * nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else if (nuevoNodo->dato< lista->dato)
    {
        lista=agregarAlPrincipio(lista, nuevoNodo);
    }
    else
    {

        nodo2 * anterior=lista;
        nodo2 * seg=lista->ste;

        while(seg!=NULL && seg->dato < nuevoNodo->dato)
        {
            anterior=seg;
            seg=seg->ste;
        }
       nuevoNodo->ste=seg;                                  // Ahora va al Final
       anterior->ste =nuevoNodo;                        // Ahora va al principio

       nuevoNodo->ante = anterior;                   //  Nueva linea Medio
        if(seg!=NULL)
        {
            seg->ante= nuevoNodo;
        }

    }
    return lista;
}
nodo2 * borrarNodo(nodo2 * lista, int dato)
{
    if(lista!=NULL)///Igual que lista simple
    {
        if(lista->dato==dato)///Igual que lista simple
        {
            nodo2*aux=lista;///Igual que lista simple
            lista=lista->ste;///Igual que lista simple
            if(lista!=NULL)        //NUEVO
                lista->ante=NULL;  //NUEVO
            free(aux);///Igual que lista simple
        }
        else
        {
            nodo2*seg=lista->ste;//Ahora se iguala a lista->siguiente
            while(seg!=NULL && seg->dato!=dato)///Igual que lista simple
            {
                seg=seg->ste; //No hago copia con ante
            }
            if( seg!= NULL)///Igual que lista simple
            {
                nodo2*ante=seg->ante; //NUEVO
                
                ante->ste = seg->ste; ///Igual que lista simple
                
                if(seg->ste!=NULL) //NUEVO
                {
                    nodo2 * siguiente = seg->ste;//NUEVO
                    siguiente->ante=ante;//NUEVO
                }
                
                free(seg); ///Igual que lista simple
            }
        }
    }

    return lista;

}
void mostrarNodo(nodo2 * aux)
{
    printf(" %d", aux->dato);
}
void recorrerYmostrar(nodo2 * lista)
{
    nodo2 * seg = lista;
    while (seg != NULL)
    {
        mostrarNodo(seg);
        seg= seg->ste;
    }
    printf("\n");
}
nodo2 * cargarLista(nodo2 * lista)
{
    char rta = 's';
    int dato;
    nodo2 * aux;
    while(rta == 's')
    {
        printf("\nIngrese un valor: ");
        scanf("%d", &dato);
        aux = crearNodo(dato);
        lista=agregarAlFinal(lista, aux);
        printf("\nContinuas?: ");
        fflush(stdin);
        scanf("%c", &rta);
    }
    return lista;
}

/*
------------------Pilas------------------
*/
typedef struct
{
    int dato;
    struct nodo * siguiente;
} nodo;
nodo * inicLista()
{
    return NULL;
}
nodo * crearNodo(int dato)
{
    nodo * aux = (nodo*)malloc(sizeof(nodo));
    aux->dato = dato;
    aux->siguiente = NULL;
    return aux;
}
nodo * agregarPpio(nodo * lista, nodo * nuevoNodo)
{

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else

    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}
int verPrimero(nodo * lista)
{
    int rta;
    if(lista)
    {
        rta=lista->dato;
    }
    return rta;

}
nodo * borrarPrimerNodo(nodo * lista)
{
    nodo * aux=lista;
    lista=lista->siguiente;
    free(aux);
    return lista;
}
void mostrarNodo(nodo * aux)
{
    printf("%d ",aux->dato);
}
void recorrerYmostrar(nodo * lista)
{
    nodo * aux=lista;
    while(aux!=NULL)
    {
        mostrarNodo(aux);
        aux=aux->siguiente;
    }
}
nodo * SubprogramaIngresarNuevoDato()
{
    int dato;
    nodo * nuevoNodo;
    printf("\nIngrese un numero:");
    scanf("%d", &dato);
    nuevoNodo = crearNodo(dato);
    return nuevoNodo;
}
#define Pila nodo*
void inicPila (Pila * pila)
{
    (*pila)=inicLista();
}
int pilavacia (Pila* pila)
{
    int rta=0;
    if ((*pila)==NULL)
    {
        rta = 1;
    }

    return rta;
}
int tope (Pila * pila)
{
    int rta=0;
    if((*pila)!=NULL)
    {
       rta=verPrimero(*pila);
    }
    return rta;
}
int desapilar (Pila * pila)
{

    int rta;
    if((*pila)!=NULL)
    {
        rta = verPrimero(*pila);
        *pila=borrarPrimerNodo(*pila);
    }

    return rta;
}
void apilar (Pila * pila, int dato)
{
    nodo * aux= crearNodo(dato);
    *pila=agregarPpio(*pila,aux);
}
void leer (Pila * pila)
{
    nodo *aux = SubprogramaIngresarNuevoDato();
    (*pila)=agregarPpio(*pila,aux);
}
void mostrar (Pila * pila)
{
    //nodo * seg = (*pila);
    printf("\nTope ");
    recorrerYmostrar(*pila);
    printf("Base\n");
}

/*
------------------Invertir Lista------------------
*/
Nodo* invertir(Nodo* lista)//retorna la lista
{
    Nodo* a=NULL;
    Nodo* b=NULL;
    Nodo* c=NULL;
    //a,b y c son tres nodos que contienen las direcciones de memoria
    //de los tres primeros nodos de la lista respectivamente.

    a=lista;
    if(a!=NULL)
    {
        b=a->ste;
        a->ste = NULL; //el primero pasa a ser el último
        if(b != NULL)
        {
            c=b->ste;
            while(c!=NULL)
            {
                b->ste = a;
                a=b;
                b=c;
                c=c->ste;
            }
            //c es igual a NULL, se llega al final de la lista. En b está el último nodo.
            b->ste = a; //última inversión de enlaces. En este punto, b es el nuevo primer nodo.
        }
        else
            b=a;
    }
    return b;
}

/*
------------------Recursividad------------------
*/
float promedioRecursivo(int A[], int validos, int i)
{
    float prom=0;

    if(i<validos)
    {
        prom = ((float)A[i]/(float)validos)+promedioRecursivo(A, validos, i+1);
    }

    return prom;

}
int factorial (int x)
{
    int rta;
    if(x==0)
    {
        rta=1;
    }
    else
    {
        rta=x*factorial(x-1);
    }
    return rta;
}
int potencia(int x, int factor)
{
    int rta;
    if(factor==0)
    {
        rta=1;
    }
    else
    {
        rta=x*potencia(x,factor-1);
    }
    return rta;
}
void muestraArregloRecursivo2(int A[], int i, int cant)
{
    if(i<cant)
    {
        printf(" %d", A[i]);
        muestraArregloRecursivo2(A, i+1, cant);
    }
}
int capicua(char A[], int i, int u)
{
    int rta=1;
    if(i<u)
    {
        if(A[i]==A[u])
        {
            rta=capicua(A,i+1,u-1);
        }
        else
        {
            rta=0;
        }
    }
    return rta;
}
int sumaRescursiva(int A[], int i, int cant)
{
    int rta=0;
    if(i==cant)
    {
        rta=0;
    }
    else
    {
        rta = A[i]+sumaRescursiva(A, i+1, cant);
    }
    return rta;
}
int menorRecursivo(int A[], int i, int cant)
{
    int m;
    /// cuando llego al final del arreglo, retorno ese valor
    /// para comparar con los de las etapas recursivas anteriores
    if(i==cant)
    {
        m=A[cant-1];
    }
    else
    {
        m=menorRecursivo(A, i+1, cant);
        if(m>A[i])
        {
            m = A[i];
        }
    }
    return m;
}

int menorEnArchivo (FILE * arch)//pide archivo abierto, archi solo
{

    int menor;
    int aux;

    if(fread(&aux,sizeof(int),1,arch)==0) /// cuando llego al final del archivo
    {
        /// me muevo uno para atras
        fseek(arch, -1*sizeof(int), SEEK_END);
        /// lo leo
        fread(&menor, sizeof(int),1,arch); /// leo el ultimo elemento para retornarlo
    }
    else
    {
        menor = menorEnArchivo(arch);

        if(aux<menor)
        {
            menor=aux;
        }
    }
    return menor;
}
void abreYmuestraMenor (char nombre[])// subprograma que inicia la conexión con el archivo y busca el menor
{
    FILE *arch=NULL;

    arch=fopen(nombre, "rb");

    if(arch!=NULL)
    {
        int menor= menorEnArchivo(arch);

        printf("\n\nEl menor en el archivo es %d", menor);

        fclose(arch);
    }
    else
    {
        printf("Paso algo muy malo...");
    }
}

//Invierte un archivo en forma recursiva
int leer(FILE * arch)
{
    int aux;
    fread(&aux, sizeof(int),1,arch);
    return aux;
}
void escribir(FILE *arch, int valor)
{
    fwrite(&valor, sizeof(int), 1, arch);
}
int cuentaRegistroArchivo(FILE * arch)
{
    int cant=0;
    fseek(arch, 0, SEEK_END);
    cant=ftell(arch)/sizeof(int);
    return cant;
}
void invierteArchivo(FILE *arch, int i, int u)
{
    int ppio;
    int fin;
    if(i<u)
    {
        fseek(arch,i*sizeof(int),SEEK_SET);
        ppio=leer(arch);
        fseek(arch, u*sizeof(int),SEEK_SET);
        fin=leer(arch);
        fseek(arch,i*sizeof(int),SEEK_SET);
        escribir(arch, fin);
        fseek(arch, u*sizeof(int),SEEK_SET);
        escribir(arch, ppio);
        invierteArchivo(arch, i+1, u-1);
    }
}
//Invierte un archivo en forma recursiva ^

int determinaElementoEnArreglo(int A[], int cant, int i, int valor)
{
    int rta=0; // supongo que el elemento no esta
    if(i<cant)
    {
        if(A[i]==valor)
        {
            rta=1;
        }
        else
        {
            rta=determinaElementoEnArreglo(A, cant,i+1, valor);
        }
    }
    return rta;
}
/*
------------------Recursividad Listas Simples------------------
*/
nodo*BuscarUltimoNodoRecursiva(nodo*lista)
{
    if(lista!=NULL)
    {
       if((lista->siguiente)!=NULL)
       {
         lista=BuscarUltimoNodo(lista->siguiente);
       }
    }
    return lista;
}

nodo*BorrarNodoRecursivo(nodo*lista,int dato)
{
    nodo*aux=NULL;
    if(lista!=NULL)
    {
        if(lista->dato==dato)
        {
            aux=lista;
            lista=lista->siguiente;
            free(aux);
        }
        else
        {
            lista->siguiente=BorrarNodoRecursivo(lista->siguiente,dato);
        }
    }
    return lista;
}

nodo*AgregarNodoEnListaRecursivo(nodo*lista,nodo*nuevoNodo) //Agregar en una lista ya ordenada
{
    nodo*aux=NULL;
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        if((lista->dato)<(nuevoNodo->dato))
        {
            nuevoNodo->siguiente=lista;
            lista=nuevoNodo;
        }
        else
        {
            lista->siguiente=AgregarNodoEnListaRecursivo(lista->siguiente,nuevoNodo);
        }
    }
    return lista;
}

nodo*InvierteLaLista(nodo*lista)
{
    nodo*primero=NULL;
    if(lista!=NULL)
    {
        primero=lista;
        lista=lista->siguiente;
        primero->siguiente=NULL;
        lista=AgregarAlFinal((InvierteLaLista(lista)),primero);
    }
    return lista;
}
void MuestraLugaresParesLista(nodo*lista,int i)
{
    if(lista!=NULL)
    {
       MuestraLugaresParesLista(lista->siguiente,i+1);
       if((i%2)==0)
       {
         printf(" [%i] ",lista->dato);
       }
    }
}
int SumaElementosDeLista(nodo*lista)
{
    int suma=0;
    if(lista!=NULL)
    {
        suma=(lista->dato)+SumaElementosDeLista(lista->siguiente);
    }
    return suma;
}
void MuestraLista(nodo*lista)
{
    if(lista!=NULL)
    {
      MuestraLista(lista->siguiente);
      printf(" [%i] ",lista->dato);
    }
}
