#include<iostream>
#include<random>

using namespace std;

const int N = 8;
const int INFTY = 10000;
const int PROFUNDITAT = 6;

typedef struct node {
    int nivell;
    char tauler[N][N];
    int n_fills;
    int valor;
    struct node **fills;
} Node;

void dibuixarTauler(char t[N][N]);

void imprimirNode(Node *node){
    cout << "Nivell: " << node->nivell << endl;
    cout << "Valor: " << node->valor << endl;
    cout << "Numero de fills: " << node->n_fills << endl;
    cout << "Fills: " << endl;
    for(int i=0;i<node->n_fills;i++) {
        cout << node->fills[i] << endl;
    }
    printf(" Tauler: \n");
    //dibuixarTauler(node->tauler);
}
void recorrerArbre(Node *pare){
    for(int Fill=0;Fill<pare->n_fills;Fill++){
        recorrerArbre(pare->fills[(pare->n_fills)-(Fill+1)]);
    }
    imprimirNode(pare);
}

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
int calcularNumFills(char t[N][N]) {
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
        p->n_fills=calcularNumFills(p->tauler);
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
void    checkS(char t[N][N],int a,int b,int *i){
    if(t[a][b]==t[a+1][b] && a<(N-1)){
        (*i)++;
        checkS(t,a+1,b,i);
    }
}

int checkCol(char t[N][N],int a,int b,int enratlla){        //enratlla 1, 2, 3 o 4 per comprovar si hi ha 1, 2, 3 o 4 en ratlla.
    if(t[a][b]==t[a+1][b]){
        int i=0;
        checkS(t,a,b,&i);
        if(i>(enratlla-2)){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

void checkO(char t[N][N],int a,int b,int *i){
    if(t[a][b]==t[a][b-1] && b>0){
        (*i)++;
        checkO(t,a,b-1,i);
    }
}

void checkE(char t[N][N],int a,int b,int *i){
    if(t[a][b]==t[a][b+1] && b<(N-1)){
        (*i)++;
        checkE(t,a,b+1,i);
    }
}

int checkFila(char t[N][N],int a,int b,int enratlla){
    if(t[a][b]==t[a][b+1] || t[a][b]==t[a][b-1]){
        int i=0;
        checkO(t,a,b,&i);
        checkE(t,a,b,&i);
        if(i>(enratlla-2)){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

void checkNO(char t[N][N],int a, int b,int *i){
    if(t[a][b]==t[a-1][b-1] && a>0 && b>0){
        (*i)++;
        checkNO(t,a-1,b-1,i);
    }
}

void checkSE(char t[N][N],int a, int b,int *i){
    if(t[a][b]==t[a+1][b+1] && a<(N-1) && b<(N-1)){
        (*i)++;
        checkSE(t,a+1,b+1,i);
    }
}

void checkNE(char t[N][N],int a, int b,int *j){
    if(t[a][b]==t[a-1][b+1] && a>0 && b<(N-1)){
        (*j)++;
        checkNE(t,a-1,b+1,j);
    }
}

void checkSO(char t[N][N],int a, int b,int *j){
    if(t[a][b]==t[a+1][b-1] && a<(N-1) && b>0){
        (*j)++;
        checkSO(t,a+1,b-1,j);
    }
}

int checkDiag(char t[N][N],int a,int b,int enratlla){
    if(t[a][b]==t[a+1][b+1] || t[a][b]==t[a+1][b-1] || t[a][b]==t[a-1][b+1] || t[a][b]==t[a-1][b-1]){
        int i=0,j=0;
        checkNO(t,a,b,&i);
        checkSE(t,a,b,&i);
        checkNE(t,a,b,&j);
        checkSO(t,a,b,&j);
        if(i>(enratlla-2) || j>(enratlla-2)){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}
int Enratlla4(Node *node){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(node->tauler[i][j]!='0'){
                if(checkFila(node->tauler,i,j,4) || checkCol(node->tauler,i,j,4) || checkDiag(node->tauler,i,j,4)){
                    return 1;
                }
            }
        }
    }
    return 0;
}
int Enratlla3lliures(Node *node){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(node->tauler[i][j]!='0'){
                if((node->tauler[i][j-1]==node->tauler[i][j] && node->tauler[i][j]==node->tauler[i][j+1]) && (j-1>0 && j+2<N)){
                    if(node->tauler[i][j+2]=='0' && node->tauler[i+1][j+2]!='0'){
                        if(node->tauler[i][j-2]=='0' && node->tauler[i+1][j-2]!='0'){
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/* int Enratlla3lliures(Node *node){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(node->tauler[i][j]!='0'){
                if(checkFila(node->tauler,i,j,3) && (j-1>0 && j+2<N)){
                    if(node->tauler[i][j+2]=='0' && node->tauler[i+1][j+2]!='0' && i<N){
                        if(node->tauler[i][j-2]=='0' && node->tauler[i+1][j-2]!='0'){
                            return 1;
                        }
                    }
                }
                if(((node->tauler[i][j]==node->tauler[i+1][j+1] && node->tauler[i][j]==node->tauler[i-1][j-1]) || (node->tauler[i][j]==node->tauler[i+1][j-1] && node->tauler[i][j]==node->tauler[i-1][j+1])) && ((i+2<N && j+2<N) && (i-1>0 && j-1>0))){
                    if((node->tauler[i+2][j+2]=='0' && node->tauler[i-2][j-2]=='0' && (node->tauler[i+3][j+2]!='0' || i+3<(N+1)) && (node->tauler[i-1][j-2]!='0'))){
                        return 1;
                    }
                    else if(node->tauler[i+2][j-2]=='0' && node->tauler[i-2][j+2]=='0' && (node->tauler[i+3][j-2]!='0' || i+3<(N+1)) && (node->tauler[i-1][j+2]!='0')){
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
} */

/* int Enratlla3(Node *node){
    int jug=0,pc=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(node->tauler[i][j]!='0'){
                if(checkCol(node->tauler,i,j,3) && node->tauler[i-1][j]=='0'){
                    if(node->tauler[i][j]=='2'){
                        pc++;
                    }
                    else{
                        jug++;
                    }
                }
                else if((node->tauler[i][j]==node->tauler[i][j-1] && node->tauler[i][j]==node->tauler[i][j+1])){
                    if(node->tauler[i][j-2]=='0' && node->tauler[i+1][j-2]!='0' && j-1>0 && i<N){
                        if(node->tauler[i][j+2]=='0' && node->tauler[i+1][j+2]!='0'){
                            if(node->tauler[i][j]=='2'){
                                pc=INFTY;
                            }
                            else{
                                jug=INFTY;
                            }
                        }
                        else if(node->tauler[i][j]=='2'){
                                pc++;
                            }
                            else{
                                jug++;
                            }
                    }
                }
                //check col
                //check fila
                //check diag
            }
        }
    }
} */

int Enratlla3(Node *node){ //Aquesta funció buscarà configuracions del tauler en les quals, hi ha tres peces alineades (vert, hortz o bé diag) les quals no estan delimitades per fitxes de l'adversari, ie estan lliures
    int jug=0,pc=0;
    for(int i=0;i<N;i++){       //CALDRIA MIRAR QUE LES DIRECCIONS ESTIGUESSIN BUIDES!!!! SINÓ, ELS TRES EN RATLLA NO VALEN TANT
        for(int j=0;j<N;j++){
            if(node->tauler[i][j]!='0'){
                if(checkFila(node->tauler,i,j,3)){
                    if(node->tauler[i][j]=='2'){
                        pc++;
                    }
                    else{
                        jug++;
                    }
                }
                else if(checkCol(node->tauler,i,j,3)){
                    if(node->tauler[i][j]=='2'){
                        pc++;
                    }
                    else{
                        jug++;
                    }
                }
                else if(checkDiag(node->tauler,i,j,3)){
                    if(node->tauler[i][j]=='2'){
                        pc++;
                    }
                    else{
                        jug++;
                    }
                }
            }
        }
    }
    return jug-pc;
}

/* int Enratlla2(Node *p){
    int jug=0,pc=0;
    for(int i=0;i<N;i++){       //CALDRIA MIRAR QUE LES DIRECCIONS ESTIGUESSIN BUIDES!!!! SINÓ, ELS TRES EN RATLLA NO VALEN RES
        for(int j=0;j<N;j++){
            if(p->tauler[i][j]!='0'){
                if(checkFila(p->tauler,i,j,3)){
                    if(p->tauler[i][j]=='2'){
                        pc++;
                    }
                    else{
                        jug++;
                    }
                }
                else if(checkCol(p->tauler,i,j,3)){
                    if(p->tauler[i][j]=='2'){
                        pc++;
                    }
                    else{
                        jug++;
                    }
                }
                else if(checkDiag(p->tauler,i,j,3)){
                    if(p->tauler[i][j]=='2'){
                        pc++;
                    }
                    else{
                        jug++;
                    }
                }
            }
        }
    }
    return jug-pc;
} */

int assignavalor(Node *node,int valor){
    if(node->nivell%2==0){
        return -valor;
    }
    else{
        return valor;
    }
}
int heuristica(Node *node,int pes_3ratlla/* ,int pes_2ratlla,int pes_1ratlla */){
    //Bàsicament, la funció heurística és una funció que avalua el valor d'un node fulla donada una taula qualsevol.
    //Aquest valor correspon a la resta entre el "potencial" del pc a fer 4 en ratlla menys el "potencial" del jugador a fer quatre en ratlla.
    //Si al tauler ja hi ha un quatre en ratlla, el valor d'aquell node fulla prendrà un valor de INFTY o -INFTY en funció de si el quatre en
    //ratlla és favorable a l'ordinador o al jugador respectivament. Si no existeixen quatres en ratlla hem de seguir un altre criteri per tal
    //de poder evaluar el tauler. PRIMERA IDEA: Per totes i cadascuna de les fitxes del tauler caldria avaluar una funció "pes", que depenent
    //de la fitxa avaluada, sumaria o restaria valor al node fulla. Aquesta funció "pes", miraria el "potencial" de la fitxa en concret i com
    //aquesta pot generar quatres en ratlla. Una primera idea seria mirar al voltant d'aquesta fitxa (a les 8 caselles al voltant d'aquesta) i
    //veure quantes n'hi ha de quin jugador i on estan col·locades. En funció de la col·locació d'aquestes fitxes adjacents calculariem el nombre
    //de quatres en ratlla que hipotèticament es podrien formar. SEGONA IDEA: El pes o valor d'una única pesa al tauler depèn del seu entorn,
    //i doncs aquest valor és una combinació lineal del nombre d'un en ratlla, de dos en ratlla i tres en ratlla del qual en forma part,
    //caldria també tenir en compte el nombre de caselles que hi ha lliures al seu voltant i doncs son les múltiples direccions d'atac a la
    //mateixa vegada. En aquesta valoració només entraran en consideració els un, dos i tres en ratlla que estiguin lliures per tots dos costats.
    //Els coeficients d'aquesta combinació lineal seran variables que es podran anar canviant per tal d'obtenir una màquina més o menys agresiva.
    //Diguem \alpha, \beta i \gamma.
    if(Enratlla4(node) || Enratlla3lliures(node)){
        return assignavalor(node,INFTY);
    }
    else{   //El tauler no conté cap quatre en ratlla i doncs hem de donar-li un valor en funció de la posició de les fitxes al tauler la funció
            //pes que dona un resultat a aquesta configuració vull que tingui la forma |a*3enratlla(p,pes_3enratlla)+b*2enratlla(p,pes_2enratlla)
            //+c*1enratlla(p,pes_1enratlla)|<INFTY (ATENCIÓ!!! Observem que aquesta funció de l'esquerra depèn nombre de fitxes al tauler i doncs
            //tot i que el tauler estigui ple, aquest valor no pot superar INFTY). Caldria afegir una funció que mirés si existeixen tres fitxes
            //al tauler alineades i que no estan envoltades per cap fitxa contraria, ja que en aquell cas és una situació win-win i se li hauria
            //d'assignar la major puntuació (INFTY)
        return assignavalor(node,pes_3ratlla*Enratlla3(node)/* +pes_2ratlla*Enratlla2(p)+pes_1ratlla*Enratlla1(p) */);
    }
}
void crearNivell(Node *pare){
    for(int Fill=0;Fill<pare->n_fills;Fill++){
        pare->fills[Fill]=crearNode(pare,Fill);
    }
}
void crearArbre(Node *pare, int profunditat){
    if(pare->nivell<profunditat){
        crearNivell(pare);
        for(int Fill=0;Fill<pare->n_fills;Fill++){
            crearArbre(pare->fills[Fill],profunditat);
        }
    }
    else{
        //Node fulla
        pare->n_fills=0;
        pare->fills=NULL;
        pare->valor=heuristica(pare,100);
    }
}

int Max(Node *pare){    //Funcions que retorna el valor màxim dels fills d'un node pare qualsevol
    int Max=(pare->fills[0])->valor;
    for(int Fill=0;Fill<pare->n_fills;Fill++){
        if(Max<(pare->fills[Fill])->valor){
            Max=(pare->fills[Fill])->valor;
        }
    }
    return Max;
}

int Min(Node *pare){    //Funcions que retorna el valor màxim dels fills d'un node pare qualsevol
    int Min=(pare->fills[0])->valor;
    for(int Fill=0;Fill<pare->n_fills;Fill++){
        if(Min>(pare->fills[Fill])->valor){
            Min=(pare->fills[Fill])->valor;
        }
    }
    return Min;
}

void minimax(Node *pare){
    for(int Fill=0;Fill<pare->n_fills;Fill++){
        if((pare->fills[Fill])->n_fills!=0){
            minimax(pare->fills[Fill]);
        }
    }
    if(pare->n_fills!=0){
        if(pare->nivell%2==0){
            pare->valor=Max(pare);
        }
        else{
            pare->valor=Min(pare);
        }
    }
}

int calculacol(Node *pare){
    for(int Fill=0;Fill<pare->n_fills;Fill++){
        if((pare->fills[Fill])->valor==pare->valor){
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    if(pare->tauler[i][j]!=(pare->fills[Fill])->tauler[i][j]){
                        //cout << j << endl;
                        return j;
                    }
                }
            }
        }
    }
}

void esborrarArbre(Node *pare){
    for(int Fill=0;Fill<pare->n_fills;Fill++){
        if((pare->fills[Fill])->n_fills!=0){
            esborrarArbre(pare->fills[Fill]);
        }
        else{
            free(pare->fills[Fill]);
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
            arrel->fills=new Node *[arrel->n_fills];        //fills és una sola adreça. Aquesta és l'adreça que contindrà l'adreça del primer fill del node arrel, però com el nombre de fills no és 1 (habitualment), les altres adreces apunten als altres fills. En el cas que calcularNumFills=8, aleshores estaria reservant 8*8=64 bytes de memòria i m'estaria quedant amb la primera adreça d'aquestes que s'assignaria com a valor a arrel->fills
            crearArbre(arrel,PROFUNDITAT);
            minimax(arrel);
            recorrerArbre(arrel);
            col=calculacol(arrel)+1;
            esborrarArbre(arrel);
        }
        modificarTauler(tauler, col-1, ronda);
        dibuixarTauler(tauler, col-1);
        check(tauler, col-1, &run);
        ronda++;
    }
    cout << "El jugador " << ronda%2 << " ha guanyat";
    return 0;
}
