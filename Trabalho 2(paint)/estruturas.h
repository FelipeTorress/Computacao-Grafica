// Estrututa de dados para o armazenamento dinamico dos pontos
// selecionados pelos algoritmos de rasterizacao
struct ponto
{
	int x;
	int y;
	bool tipo;//false = interface, true = desenho
	ponto * prox;
};


// struct reta{
// 	int x1;
// 	int y1;
// 	int x2;
// 	int y2;
// };
// 
// struct circuloStruct{
// 	int x;
// 	int y;
// 	int raio;  	
// };
// 
// 
// reta * pushReta(int x1, int y1,int x2,int y2){
// 	reta pnt;
// 	pnt = new reta;
// 	pnt->x1= x1;
// 	pnt->y1= y1;
// 	pnt->x2= x2;
// 	pnt->y2= y2;
// 	return pnt;
// }