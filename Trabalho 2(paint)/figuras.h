void bresenham (double x1, double y1, double x2, double y2, bool tipo){
	double Vx = x2 - x1;
	double Vy = y2 - y1;
	double d = 2*Vy - Vx;
	double incE = 2*Vy;
	double incNE = 2*(Vy - Vx);
	
	//Armazenando os extremos para desenho
    pontos = pushPonto((int)x1,(int)y1,tipo);
    pontos = pushPonto((int)x2,(int)y2,tipo);
	
	while(x1<x2){
		if(d < 0){
			d += incE; 
		}else{
			d += incNE;
			y1++;
		}
		pontos = pushPonto((int)x1,(int)y1,tipo);
		x1++;
	}
	drawPontos();
}

void reducao_primeiro_octante(double x0, double y0, double x1, double y1, bool tipo) {
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    pontos = pushPonto((int)x0,(int)y0,tipo);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
	bresenham(x0,y0,x1,y1,tipo);
}

//----------------------------------------------------
void quadrilatero(double p1,double q1,double p2,double q2,bool tipo){	
	reducao_primeiro_octante(p2,q1,p1,q1,tipo);
	reducao_primeiro_octante(p1,q1,p1,q2,tipo);
	reducao_primeiro_octante(p1,q2,p2,q2,tipo);
	reducao_primeiro_octante(p2,q2,p2,q1,tipo);
	drawPontos();
}

//----------------------------------------------------
void triangulo(double p1, double q1, double p2, double q2, double p3, double q3, bool tipo){
	reducao_primeiro_octante(p1, q1, p2, q2,tipo);
	reducao_primeiro_octante(p2, q2, p3, q3,tipo);
	reducao_primeiro_octante(p3, q3, p1, q1,tipo);
	drawPontos();
}

//----------------------------------------------------
void poligono_draw(double x1, double y1, bool tipo){
	if(x_backup_poligono == -1 && y_backup_poligono == -1){
		x_backup_poligono = x1;
		y_backup_poligono = y1;
		inicial[0] = x1;
		inicial[1] = y1;
		pontosReta = pontos;
	}else{
		reducao_primeiro_octante(x_backup_poligono,y_backup_poligono,x1,y1,tipo);
		x_backup_poligono = x1;
		y_backup_poligono = y1;
	}
	drawPontos();
}

//-----------------------------------------------------------
void pontos_circulo(int x, int y, int xi, int yi, bool tipo){
	pontos = pushPonto((xi + x), (yi + y),tipo);
	pontos = pushPonto((yi + x), (xi + y),tipo);
	pontos = pushPonto((-xi + x), (yi + y),tipo);
	pontos = pushPonto((-yi + x), (xi + y),tipo);
	pontos = pushPonto((xi + x), (-yi + y),tipo);
	pontos = pushPonto((yi + x), (-xi + y),tipo);
	pontos = pushPonto((-xi + x), (-yi + y),tipo);
	pontos = pushPonto((-yi + x), (-xi + y),tipo);
}

double calculaDistancia(int x1, int y1, int x2, int y2){
    return sqrt( pow(x2-x1,2) + pow(y2-y1, 2) );
}

void circunferencia(double x, double y, double r, bool tipo){
	int d = 1 - r, variaE = 4, variaSe = -2 * r + 5;
	int xi = 0, yi = r;

	pontos = pushPonto((int)x, (int) y,tipo);

	while(yi >= xi)
	{
		if(d < 0)
		{
			d += variaE;
			variaE += 2;
			variaSe += 2;
			pontos_circulo((int)x, (int)y, xi, yi,tipo);
		}
		else
		{
			d += variaSe;
			variaE += 2;
			variaSe += 4;
			pontos_circulo(x, y, xi, yi,tipo);
			yi--;
		}
		xi++;
	}
	drawPontos();
}


//---------------------------------------------------------------------------
void retaImediata(double x1, double y1, double x2, double y2, bool tipo){
    double m, b, yd, xd;
    double xmin, xmax,ymin,ymax;
    //Armazenando os extremos para desenho
    pontos = pushPonto((int)x1,(int)y1,tipo);
    pontos = pushPonto((int)x2,(int)y2,tipo);
    
    if(x2-x1 != 0){ //Evita a divisão por zero
        m = (y2-y1)/(x2-x1);
        b = y1 - (m*x1);

        if(m>=-1 && m <= 1){ // Verifica se o declive da reta tem tg de -1 a 1, se verdadeira calcula incrementando x
            xmin = (x1 < x2)? x1 : x2;
            xmax = (x1 > x2)? x1 : x2;

            for(int x = (int)xmin+1; x < xmax; x++){
                yd = (m*x)+b;
                yd = floor(0.5+yd);
                pontos = pushPonto(x,(int)yd,tipo);
            }
        }else{ // Se menor que -1 ou maior que 1, calcula incrementado os valores de y
            ymin = (y1 < y2)? y1 : y2;
            ymax = (y1 > y2)? y1 : y2;

            for(int y = (int)ymin + 1; y < ymax; y++){
                xd = (y - b)/m;
                xd = floor(0.5+xd);
                pontos = pushPonto((int)xd,y,tipo);
            }
        }

    }else{ // se x2-x1 == 0, reta perpendicular ao eixo x
        ymin = (y1 < y2)? y1 : y2;
        ymax = (y1 > y2)? y1 : y2;
        for(int y = (int)ymin + 1; y < ymax; y++){
            pontos = pushPonto((int)x1,y,tipo);
        }
    }
}