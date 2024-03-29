ponto * deletar() //retirar os pontos da reta que sera redesenhada
{
	ponto * pnt;
	pnt = NULL;
	ponto * pnt2;
	pnt2 = pontos;

	while(pnt2 != pontosReta)
	{
		if(pontos->tipo)
		{
			pnt = pnt2->prox;
			delete pnt2;
			pnt2 = pnt;
			continue;
		}
		pnt2 = pnt2->prox;
	}
	pontosReta = pnt2;
	return pnt2;
}

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

void rotacao(int tipo)
{
	ponto * pnt;
	pnt = pontos;
	int xaux =0, yaux=0, inix =0, iniy =0,lastx = 0, lasty =0;
	double rad = 5 * M_PI / 180;
	
	
	while (pnt != pontosReta)
	{
		if(pnt->tipo)
		{
			if(inix ==0 && iniy ==0){
				inix = pnt->x;
				iniy = pnt->y;
				//printf("inix:%d,iniy:%d\n",inix,iniy);
				translacao(-inix,-iniy);
			}
			xaux = pnt->x;
			yaux = pnt->y;
			pnt->x = (int)(xaux * cos(rad) - yaux * sin(rad));
			pnt->y = (int)(xaux * sin(rad) + yaux * cos(rad));
			//lastx = pnt->x;
			//lasty = pnt->y;
		}
		pnt = pnt->prox;
	};
	translacao(inix,iniy);
	
	inix =0;iniy =0;
	
	if(tipo == RETA){
		pnt = pontos;
		while (pnt != pontosReta)
	{
		if(pnt->tipo)
		{
			if(inix ==0 && iniy ==0){
				inix = pnt->x;
				iniy = pnt->y;
			}
			lastx = pnt->x;
			lasty = pnt->y;
		}
		pnt = pnt->prox;
	}
	
		pontos = deletar();
		pontosReta = pontos;
		reducao_primeiro_octante(lastx,lasty,inix,iniy,true);
	
	}

}
