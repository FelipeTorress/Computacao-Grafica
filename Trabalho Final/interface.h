void desenhar_interface ()
{// desenhando as opcoes da tela
	//formas geometricas do menu lateral
	quadrilatero(34.0, 597, 4.0, 420,false);

	quadrilatero(34.0, 590, 4.0, 566,false);
	reducao_primeiro_octante(8.0, 570.0, 31.0, 585.0,false);

	quadrilatero(34.0, 560, 4.0, 536,false);
	triangulo(17, 555, 9, 540, 28, 540,false);

	quadrilatero(34.0, 530, 4.0, 506,false);
	quadrilatero(9, 523, 27, 515,false);

	quadrilatero(34.0, 500, 4.0, 476,false);
	reducao_primeiro_octante(28.0, 495.0, 28.0, 481.0,false);
	reducao_primeiro_octante(28.0, 481.0, 11.0, 481.0,false);
	reducao_primeiro_octante(11.0, 482.0, 17.0, 488.0,false);
	reducao_primeiro_octante(17.0, 488.0, 11.0, 496.0,false);
	reducao_primeiro_octante(11.0, 496.0, 28.0, 495.0,false);

	quadrilatero(34.0, 440, 4.0, 416,false);
	reducao_primeiro_octante(8.0, 438.0, 31.0, 424.0,false);
	reducao_primeiro_octante(8.0, 437.0, 31.0, 423.0,false);
	reducao_primeiro_octante(8.0, 424.0, 31.0,  438.0,false);
	reducao_primeiro_octante(8.0, 423.0, 31.0,  437.0,false);

	quadrilatero(34.0, 470, 4.0, 446,false);
	circunferencia(19.0, 458.0, 7.0,false);

	//transformacoes do menu lateral
	quadrilatero(34.0, 380, 4.0, 356,false);
	reducao_primeiro_octante(6.0, 368.0, 32.0, 368.0,false);
	reducao_primeiro_octante(6.0, 368.0, 13.0, 375.0,false);
	reducao_primeiro_octante(6.0, 368.0, 13.0, 361.0,false);
	reducao_primeiro_octante(32.0, 368.0, 25.0, 375.0,false);
	reducao_primeiro_octante(32.0, 368.0, 25.0, 361.0,false);
	
	quadrilatero(34.0, 350, 4.0, 326,false);
	reducao_primeiro_octante(6.0, 347.0, 30.0, 330.0,false);
	reducao_primeiro_octante(6.0, 347.0, 10.0, 335.0,false);
	reducao_primeiro_octante(6.0, 347.0, 17.0, 347.0,false);
	reducao_primeiro_octante(30.0, 330.0, 18.0, 330.0,false);
	reducao_primeiro_octante(30.0, 330.0, 25.0, 342.0,false);
	
	
	quadrilatero(34.0, 320, 4.0, 296,false);
	reducao_primeiro_octante(6.0, 313.0, 20.0, 300.0,false);
	reducao_primeiro_octante(6.0, 313.0, 18.0, 313.0,false);
	reducao_primeiro_octante(20.0, 300.0, 32.0, 300.0,false);
	reducao_primeiro_octante(32.0, 300.0, 18.0, 313.0,false);
	
	quadrilatero(34.0, 290, 4.0, 266,false);
	reducao_primeiro_octante(10.0, 278.0, 28.0, 278.0,false);
	reducao_primeiro_octante(10.0, 278.0, 15.0, 273.0,false);
	reducao_primeiro_octante(10.0, 278.0, 15.0, 283.0,false);
	reducao_primeiro_octante(8.0, 270.0, 8.0, 287.0,false);
	reducao_primeiro_octante(30.0, 270.0, 30.0, 287.0,false);
	
	quadrilatero(34.0, 260, 4.0, 236,false);
	circunferencia(19.0, 248.0, 7.0,false);
	reducao_primeiro_octante(12.0, 250.0, 12.0, 257.0,false);
	reducao_primeiro_octante(12.0, 250.0, 19.0, 250.0,false);
}

void setEstado(int e)
{
	state = e;
	if(e != 3)
	{
		dois_pontos = true;
	}
	else
	{
		dois_pontos = false;
	}
	click1 = false, click2 = false, click3 = false;
}

void desenho(int x, int  y)
{

	switch (state)
	{
	case 0:

		break;
	case 1://linha
		if(click1 && click2)
		{
			pontosReta = pontos;
			//retas = pushReta(x_1, y_1, x_2, y_2);
			reducao_primeiro_octante(x_1, y_1, x_2, y_2,true);
			drawPontos();
			click1 = false;
			click2 = false;
		}
		desenhar = false;
		break;

	case 2://quadrilatero
		if(click1 && click2)
		{
			pontosReta = pontos;
			quadrilatero(x_1, y_1, x_2, y_2,true);
			drawPontos();
			click1 = false;
			click2 = false;
		}
		desenhar = false;
		break;

	case 3://triangulo
		if(click1 && click2 && click3)
		{
			pontosReta = pontos;
			triangulo(x_1, y_1, x_2, y_2, x_3, y_3,true);
			drawPontos();
			click1 = false;
			click2 = false;
			click3 = false;
		}
		desenhar = false;
		break;

	case 4://poligono
		if(click1)
		{
			poligono_draw(x_1, y_1,true);
			drawPontos();
			click1 = false;
			inicial[0] = -1;
			inicial[1] = -1;
		}
		desenhar = false;
		break;

	case 5://circulo
		if(click1)
		{
			if(inicial[0] == -1 && inicial[1] == -1)
			{
				inicial[0] = x_1;
				inicial[1] = y_1;
				click1 = false;
				return;
			}
			pontosReta = pontos;
			circunferencia(inicial[0], inicial[1],calculaDistancia((int)inicial[0], (int)inicial[1], (int)x_1, (int)y_1),true);
			drawPontos();
			click1 = false;
			inicial[0] = -1;
			inicial[1] = -1;
		}
		desenhar = false;
		break;

	case 6:
		break;

	default:
		break;
	}
}
