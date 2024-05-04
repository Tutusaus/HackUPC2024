#include<iostream>

using namespace std;

const int N = 8;
const int INFTY = 10000;

typedef struct node {
    int nivell;
    char tauler[N][N];
    int n_fills;
    int valor;
    struct node **fills;
} Node;

void copiaTauler(char t1[N][N],char t2[N][N]){  //copia el tauler del node 1 al node 2
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            t2[i][j]=t1[i][j];
        }
    }
}
int calculaColumna(char t[N][N],int fill_index){
    int index=0;
    for(int i=0;i<N;i++){
        if(t[0][i]=='0'){
            if(fill_index==index){
                return i;
            }
            index++;
        }
    }
}
int calculaFila(char t[N][N],int col){
    for(int i=0;i<N;i++){
        if(t[(N-1)-i][col]=='0'){
            return (N-1)-i;
        }
    }
}
bool quatrenratlla(char t[N][N], int fila, int col) {
    for(int j=-1;j<2;j++) {
        for(int i=-1;i<2;i++) {
            if(i!=0 or j!=0) {
                if(t[fila][col] == t[fila+j][col+i]) {
                    int direcx = i-fila;
                    int direcy = j-col;
                    //cout << tauler[fila][col] << tauler[i][j] << tauler[i+direcx][j+direcy] << tauler[i+2*direcx][j+2*direcy] << endl;
                    if(t[fila][col]==t[i+direcx][j+direcy] and t[fila][col]==t[i-direcx][j-direcy]) {
                        //cout << tauler[fila][col] << tauler[i+direcx][j+direcy] << tauler[i-direcx][j-direcy];
                        if(t[i+direcx][j+direcy]==t[i+2*direcx][j+2*direcy] or t[i-direcx][j-direcy]==t[i-2*direcx][j-2*direcy]) {
                            return false;
                        }
                    }
                    if(t[fila][col]==t[i+direcx][j+direcy] and t[fila][col]==t[i+2*direcx][j+2*direcy]) {
                        return false;
                    }
                }
            }
        }
    }
}
void aplicarTirada(int nivell,char t[N][N],int fila,int columna){
    if(nivell%2==1){
        t[fila][columna]='2';   //PC
    }
    else{
        t[fila][columna]='1';   //Jugador
    }
}
int calculaNumFills(char t[N][N]) {
    int num_de_cols_plenes=0;
    for(int i=0;i<N;i++){
        if(t[0][i]!='0'){
            num_de_cols_plenes++;
        }
    }
    return N-num_de_cols_plenes;
}
Node *crearNode(Node *pare,int fill_index){ // Aquesta funció té com a arguments l'adreça del node pare que la genera, l'índex d'aquest (fill número "tal" del node pare), i nivell on es troba el node (si és 2 llavors aquest node passa a ser un "node fulla")
    Node *p=new Node;           // Creem l'adreça de memòria que farà referència al primer fill de tots els possibles fills del node pare. Davant duu la paraula Node perquè aquesta adreça contindrà nodes.
    copiaTauler(pare->tauler,p->tauler);    // Copiem el tauler del node pare al node fill, posteriorment aplicarem la corresponent jugada.
    p->nivell=(pare->nivell)+1;             // Incrementem el nivell a nivell++ per tots els fills del node pare.
    int col=calculaColumna(p->tauler,fill_index); // Calculem la columna on s'aplicarà la següent jugada.
    int fila=calculaFila(p->tauler,col);          // Calculem la fila on s'aplicarà la següent jugada.
    aplicarTirada(p->nivell,p->tauler,fila,col);  // Un cop calculada la fila i la columna on caldrà aplicar la següent jugada, modifiquen el tauler amb la fitxa corresponent

    if(quatrenratlla(p->tauler, fila, col)) {
        p->n_fills=0;
        p->fills=nullptr;
        if(p->nivell%2==0) {
            p->valor=-INFTY;
        }
        else {
            p->valor=INFTY;
        }
    }
    else {
        p->valor=0;
        p->n_fills=calculaNumFills(p->tauler);
        p->fills= new Node *[p->n_fills];
    }
    return p;
}
void dibuixarTauler(char tauler[N][N], int col) {
    int topLeft = 201;
    int topRight = 187;
    int botLeft = 200;
    int botRight = 188;
    int vLeft = 185;
    int vRight = 204;
    int hBot = 203;
    int hTop = 202;
    int Horizontal = 205;
    int Vertical = 186;
    int cross = 206;
    int space = 32;
    string X = " X ";
    string O = " O ";


    cout << char(topLeft);
    for (int i = 0; i < 7; i++) {
        for (int i = 0; i < 3; i++) {
            cout << char(Horizontal);
        }
        cout << char(hBot);
    }
    cout << char(Horizontal) << char(Horizontal) << char(Horizontal) << char(topRight) << endl;


    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {
            cout << char(Vertical);
            if (tauler[i][j] == '1') {
                cout << X;
            } else if (tauler[i][j] == '2') {
                cout << O;
            } else {
                for (int k = 0; k < 3; k++) {
                    cout << char(space);
                }
            }
        }
        cout << char(Vertical) << endl;

        if (i < 7) {
            cout << char(vRight);
            for (int i = 0; i < 7; i++) {
                for (int i = 0; i < 3; i++) {
                    cout << char(Horizontal);
                }
                cout << char(cross);
            }
            cout << char(Horizontal) << char(Horizontal) << char(Horizontal) << char(vLeft) << endl;
        }
    }

    cout << char(botLeft);
    for (int i = 0; i < 7; i++) {
        for (int i = 0; i < 3; i++) {
            cout << char(Horizontal);
        }
        cout << char(hTop);
    }
    cout << char(Horizontal) << char(Horizontal) << char(Horizontal) << char(botRight) << endl;
    cout << "  ";
    for(int i=0;i<N;i++) {
        cout << i+1 << "   ";
    }
    cout << endl;
}
void inicialitzarTauler (char tauler[N][N]){
    for (int fila = 0; fila < N ;fila++){
        for(int col = 0; col<N ; col++){
            tauler[fila][col] = '0';
        }
    }

}
void imprimirTauler(char tauler[N][N]){
    for (int fila = 0; fila < N ;fila++){
        for(int col = 0; col<N ; col++){
            cout<< tauler[fila][col];
        }
        cout<< endl;
    }
}
void modificarTauler(char tauler[N][N], int col, int ronda) {
    for (int i=N-1; i>=0; i--){
        if(tauler[i][col] == '0'){
            if(ronda%2!=0){
                tauler[i][col] = '1';
            }
            else {
                tauler[i][col] = '2';
            }
            break;
        }
    }
}
void checkD(char tauler[N][N], int fila, int col, int i, int j, bool *run) {
    int direcx = i-fila;
    int direcy = j-col;
    //cout << tauler[fila][col] << tauler[i][j] << tauler[i+direcx][j+direcy] << tauler[i+2*direcx][j+2*direcy] << endl;
    if(tauler[fila][col]==tauler[i+direcx][j+direcy] and tauler[fila][col]==tauler[i-direcx][j-direcy]) {
        //cout << tauler[fila][col] << tauler[i+direcx][j+direcy] << tauler[i-direcx][j-direcy];
        if(tauler[i+direcx][j+direcy]==tauler[i+2*direcx][j+2*direcy] or tauler[i-direcx][j-direcy]==tauler[i-2*direcx][j-2*direcy]) {
            *run = false;
        }
    }
    if(tauler[fila][col]==tauler[i+direcx][j+direcy] and tauler[fila][col]==tauler[i+2*direcx][j+2*direcy]) {
       *run = false;
    }
}
void check(char tauler[N][N], int col, bool *run) {
    int fila=0;
    while(tauler[fila][col] == '0') {
        fila++;
    }
    for(int j=-1;j<2;j++) {
        for(int i=-1;i<2;i++) {
            if(i!=0 or j!=0) {
                if(tauler[fila][col] == tauler[fila+j][col+i]) {
                    checkD(tauler, fila, col, fila+j, col+i, run);
                }
            }
        }
    }
}
void crearNivell(Node *pare){
    for(int fill=0;fill<pare->n_fills;fill++){
        pare->fills[fill]=crearNode(pare,fill);
    }
}
void crearArbre(Node *pare, int profunditat){
    if(pare->nivell<profunditat){
        crearNivell(pare);
        for(int fill=0;fill<pare->n_fills;fill++){
            crearArbre(pare->fills[fill],profunditat);
        }
    }
    else{
        //Node fulla
        pare->n_fills=0;
        pare->fills=NULL;
        pare->valor=0;
    }
}
void torn(char t[N][N], int ronda, int *fila, int *columna) {
    int n;

    if((ronda%2)==1){
        cout << "A quina columna voleu tirar la fitxa? ";
        cin >> n;
        while(nFora(n) || colPlena(n,t)){
            scanf("%d",&n);
        }
    }
    else{
        double time_spent = 0;
        clock_t begin = clock();
        //creo un apuntador a un Node (adreça) que té una mida de 88 bytes
        Node *arrel=malloc(sizeof(Node));
        copiaTauler(t,arrel->tauler);   //el tauler es copia a la variable tauler de l'arrel
        arrel->nivell=0;
        arrel->valor=0;
        arrel->n_fills=calcularNumFills(arrel->tauler); //el nombre de fills correspon amb el nombre de caselles del tauler menys el nombre de columnes que son plenes
        arrel->fills=malloc(arrel->n_fills * sizeof(Node *));    //fills és una sola adreça. Aquesta és l'adreça que contindrà l'adreça del primer fill del node arrel, però com el nombre de fills no és 1 (habitualment), les altres adreces apunten als altres fills. En el cas que calcularNumFills=8, aleshores estaria reservant 8*8=64 bytes de memòria i m'estaria quedant amb la primera adreça d'aquestes que s'assignaria com a valor a arrel->fills
        //puc crear un arbre de dos nivells per sota
        crearArbre(arrel,PROFUNDITAT);
        minimax(arrel);
        //recorrerArbre(arrel);
        n=calculacol(arrel)+1;
        esborrarArbre(arrel);
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("The elapsed time is %f seconds", time_spent);
    }
    if(ronda==1){
        n=4;
    }

    for(int i=0;i<N;i++){
        if(t[(N-1)-i][n-1]=='0'){
            if((ronda%2)+1==1){
                t[(N-1)-i][n-1]='1';    //JUGADOR
            }
            else{
                t[(N-1)-i][n-1]='2';    //PC
            }
            *fila=(N-1)-i;                  //0-7
            *columna=n-1;                   //0-7
            break;
        }
    }
}

int main(){
    bool run = true;
    int ronda = 1;
    char tauler[N][N];
    inicialitzarTauler(tauler);

    while(run) {
        int col;

        if(ronda%2==1) {
            cout << "A quina columna vols tirar? ";
            cin >> col;
        }
        else{
            Node *arrel=new Node;
            copiaTauler(tauler,arrel->tauler);   //el tauler es copia a la variable tauler de l'arrel
            arrel->nivell=0;
            arrel->valor=0;
            arrel->n_fills=calcularNumFills(arrel->tauler); //el nombre de fills correspon amb el nombre de caselles del tauler menys el nombre de columnes que son plenes
            arrel->fills=new Node *[arrel->n_fills]         //fills és una sola adreça. Aquesta és l'adreça que contindrà l'adreça del primer fill del node arrel, però com el nombre de fills no és 1 (habitualment), les altres adreces apunten als altres fills. En el cas que calcularNumFills=8, aleshores estaria reservant 8*8=64 bytes de memòria i m'estaria quedant amb la primera adreça d'aquestes que s'assignaria com a valor a arrel->fills

        }
        modificarTauler(tauler, col-1, ronda);
        dibuixarTauler(tauler, col-1);
        check(tauler, col-1, &run);
        ronda++;
    }
    cout << "El jugador " << ronda%2 << " ha guanyat";
    return 0;
}
