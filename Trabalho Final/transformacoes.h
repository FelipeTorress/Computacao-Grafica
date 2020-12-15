void translacao(double tx, double ty)
{
	ponto * pnt;
	pnt = pontos;

	while(pnt != pontosReta )
	{
		if(pnt->tipo)
		{
			pnt->x = pnt->x + (int) tx;
			pnt->y = pnt->y + (int) ty;
		}
		pnt = pnt->prox;
	}
}

void escala(double e, int tipo)
{
	ponto * pnt;
	pnt = pontos;
	int inix = 0;
	int iniy = 0;

	int xt = 0 , yt = 0;


	if(tipo == RETA || tipo == QUADRADO || tipo == TRIANGULO || tipo == POLIGONO)
	{
		while(pnt != pontosReta )
		{
			if(pnt->tipo)
			{

				if(inix == 0 && iniy == 0)
				{
					inix = pnt->x;
					iniy = pnt->y;
					translacao(-inix, - iniy);
				}
				pnt->x = (int)(e * pnt->x);
				pnt->y = (int)(e * pnt->y);

				if(xt == 0 && yt == 0)
				{
					xt = pnt->x;
					yt = pnt->y;
				}
				else
				{
					reducao_primeiro_octante(xt, yt, pnt->x, pnt->y, true);
					xt = pnt->x;
					yt = pnt->y;
				}
			}
			pnt = pnt->prox;
		}
	}
	else
	{

		while(pnt != pontosReta )
		{
			if(pnt->tipo)
			{
				if(inix == 0 && iniy == 0)
				{
					inix = pnt->x;
					iniy = pnt->y;
					translacao(-inix, - iniy);
				}
				pnt->x = (int)(e * pnt->x);
				pnt->y = (int)(e * pnt->y);
			}
			pnt = pnt->prox;
		}
	}
	translacao(inix, iniy);
}

void cisalhamento(double valor, char eixo, int tipo)
{
	ponto * pnt;
	pnt = pontos;
	int inix = 0;
	int iniy = 0;
	int xt = 0 , yt = 0;

	if(tipo == RETA || tipo == QUADRADO || tipo == TRIANGULO || tipo == POLIGONO)
	{
		if(eixo == 'x' || eixo == 'X')
		{
			while(pnt != pontosReta )
			{
				if(pnt->tipo)
				{

					if(inix == 0 && iniy == 0)
					{
						inix = pnt->x;
						iniy = pnt->y;
						translacao(-inix, - iniy);
					}
					//operacao
					pnt->x = (int)(pnt->x + (valor * pnt->y) );

					if(xt == 0 && yt == 0)
					{
						xt = pnt->x;
						yt = pnt->y;
					}
					else
					{
						reducao_primeiro_octante(xt, yt, pnt->x, pnt->y, true);
						xt = pnt->x;
						yt = pnt->y;
					}
				}
				pnt = pnt->prox;
			}
		}
		else
		{
			while(pnt != pontosReta )
			{
				if(pnt->tipo)
				{

					if(inix == 0 && iniy == 0)
					{
						inix = pnt->x;
						iniy = pnt->y;
						translacao(-inix, - iniy);
					}
					//operacao
					pnt->y = (int)(pnt->y + (valor * pnt->x) );

					if(xt == 0 && yt == 0)
					{
						xt = pnt->x;
						yt = pnt->y;
					}
					else
					{
						reducao_primeiro_octante(xt, yt, pnt->x, pnt->y, true);
						xt = pnt->x;
						yt = pnt->y;
					}
				}
				pnt = pnt->prox;
			}
		}
		translacao(inix, iniy);
	}
	else
	{
		if(eixo == 'x' || eixo == 'X')
		{
			while(pnt != pontosReta )
			{
				if(pnt->tipo)
				{
					if(inix == 0 && iniy == 0)
					{
						inix = pnt->x;
						iniy = pnt->y;
						translacao(-inix, - iniy);
					}
					pnt->x = (int)(pnt->x + (valor * pnt->y) );

				}
				pnt = pnt->prox;
			}
		}
		else
		{
			while(pnt != pontosReta )
			{
				if(pnt->tipo)
				{
					if(inix == 0 && iniy == 0)
					{
						inix = pnt->x;
						iniy = pnt->y;
						translacao(-inix, - iniy);
					}
					//operacao
					pnt->y = (int)(pnt->y + (valor * pnt->x) );

				}
				pnt = pnt->prox;
			}
		}

		translacao(inix, iniy);
	}


}

void reflexao(char eixo, int tipo)
{
	ponto * pnt;
	pnt = pontos;
	int inix = 0;
	int iniy = 0;

	if(tipo == RETA || tipo == QUADRADO || tipo == TRIANGULO || tipo == POLIGONO)
	{
		if(eixo == 'x' || eixo == 'X')
		{
			while(pnt != pontosReta )
			{
				if(pnt->tipo)
				{

					if(inix == 0 && iniy == 0)
					{
						inix = pnt->x;
						iniy = pnt->y;
						translacao(-inix, - iniy);
					}
					//operacao
					pnt->x = pnt->x * -1;

				}
				pnt = pnt->prox;
			}
		}
		else
		{
			while(pnt != pontosReta )
			{
				if(pnt->tipo)
				{

					if(inix == 0 && iniy == 0)
					{
						inix = pnt->x;
						iniy = pnt->y;
						translacao(-inix, - iniy);
					}
					//operacao
					pnt->y = pnt->y * -1 ;

				}
				pnt = pnt->prox;
			}
		}
		translacao(inix, iniy);
	}
	else
	{
		if(eixo == 'x' || eixo == 'X')
		{
			while(pnt != pontosReta )
			{
				if(pnt->tipo)
				{
					if(inix == 0 && iniy == 0)
					{
						inix = pnt->x;
						iniy = pnt->y;
						translacao(-inix, - iniy);
					}
					pnt->x = pnt->x * -1;

				}
				pnt = pnt->prox;
			}
		}
		else
		{
			while(pnt != pontosReta )
			{
				if(pnt->tipo)
				{
					if(inix == 0 && iniy == 0)
					{
						inix = pnt->x;
						iniy = pnt->y;
						translacao(-inix, - iniy);
					}
					//operacao
					pnt->y = pnt->y * -1 ;

				}
				pnt = pnt->prox;
			}
		}

		translacao(inix, iniy);
	}
}

 
void rotacao()
{
	ponto * pnt;
	pnt = pontos;
	int xaux =0, yaux=0, inix =0, iniy =0;
	double rad = 5 * M_PI / 180;
	
	
	while (pnt != pontosReta)
	{
		if(pnt->tipo)
		{
			if(inix ==0 && iniy ==0){
				inix = pnt->x;
				iniy = pnt->y;
				translacao(-inix,-iniy);
			}
			xaux = pnt->x;
			yaux = pnt->y;
			pnt->x = (int)(xaux * cos(rad) - yaux * sin(rad));
			pnt->y = (int)(xaux * sin(rad) + yaux * cos(rad));
			
		}
		pnt = pnt->prox;
	};
	translacao(inix,iniy);
}
