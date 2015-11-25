int updateCount_me(float X[],float Y[],int coinCount[])
{
	int black_count=0,white_count=0,red_count=0,toReturn=0;
	if(X[1]==2.0f)	black_count = black_count + 1;
	if(X[2]==2.0f)	black_count = black_count + 1;
	if(X[3]==2.0f)	white_count = white_count + 1;
	if(X[4]==2.0f)	white_count = white_count + 1;
	if(X[5]==2.0f)	{ red_count = red_count + 1;  }
	if(((white_count - coinCount[1]) > 0) && X[0]!=2.0f) {toReturn = 1;score_4p[0]=score_4p[0]+2;}
	if(((red_count - coinCount[2]) > 0) && X[0]!=2.0f) {toReturn = 1;isRed_me = 'y';score_4p[0]=score_4p[0]+3;}
	coinCount[0] = black_count;
	coinCount[1] = white_count;
	coinCount[2] = red_count;
	return toReturn;
}
int updateCount_other(float X[],float Y[],int coinCount[])
{
	int black_count=0,white_count=0,red_count=0,toReturn=0;
	if(X[1]==2.0f)	black_count = black_count + 1;
	if(X[2]==2.0f)	black_count = black_count + 1;
	if(X[3]==2.0f)	white_count = white_count + 1;
	if(X[4]==2.0f)	white_count = white_count + 1;
	if(X[5]==2.0f)	{ red_count = red_count + 1; }
	if(chance[1]=='y' || chance[3]=='y')
	{
		if(((black_count - coinCount[0]) > 0) && X[0]!=2.0f) {toReturn = 1;score_4p[1]=score_4p[1]+2;}
		if(((red_count - coinCount[2]) > 0) && X[0]!=2.0f) {toReturn = 1;isRed_other = 'y';score_4p[1]=score_4p[1]+3;}
	}
	else if(chance[0]=='y')
	{
		if(((white_count - coinCount[1]) > 0) && X[0]!=2.0f) {toReturn = 1;score_4p[0]=score_4p[0]+2;}
		if(((red_count - coinCount[2]) > 0) && X[0]!=2.0f) {toReturn = 1;isRed_me = 'y';score_4p[0]=score_4p[0]+3;}
	}	
	coinCount[0] = black_count;
	coinCount[1] = white_count;
	coinCount[2] = red_count;
	return toReturn;
}
int position_replace(float X[], float Y[])
{
	int i,j1=0,j2=0,j3=0,j4=0,j5=0;
	for(i=0;i<6;i++)
	{
		if(distance(0.0f,0.0f,X[i],Y[i]) < 2*r_cn)
		{
			j1 = 1;
			break;
		}
	}
	if(j1 == 0) return 1;
	for(i=0;i<6;i++)
	{
		if(distance(-0.41f,0.0f,X[i],Y[i]) < 2*r_cn)
		{
			j2 = 1;
			break;
		}
	}
	if(j2 == 0) return 2;
	for(i=0;i<6;i++)
	{
		if(distance(0.41f,0.0f,X[i],Y[i]) < 2*r_cn)
		{
			j3 = 1;
			break;
		}
	}
	if(j3 == 0) return 3;
	for(i=0;i<6;i++)
	{
		if(distance(0.0f,-0.41f,X[i],Y[i]) < 2*r_cn)
		{
			j4 = 1;
			break;
		}
	}
	if(j4 == 0) return 4;
	for(i=0;i<6;i++)
	{
		if(distance(0.0f,0.41f,X[i],Y[i]) < 2*r_cn)
		{
			j5 = 1;
			break;
		}
	}
	if(j5 == 0) return 5;
	return 6;
}

int present_b4(float x, float y)
{
	int i;
	for(i=1;i<6;i++)
	{
		if(distance(x,y,X[i],Y[i]) <= r_cn+r_str ) return 0;
	}
	return 1;
}

void update_chance(float Vx[], float Vy[], char chance[])
{
	int i,j,k,l;
	float x_r,y_r,x_of_str=0.0f,y_of_str=0.0f;
	char cchek='x';
	if(isStrikerHitByMe=='y' && chance[2]=='y')
	{
		for(i=0;i<6;i++)
		{
			if(Vx[i]!=0.0f || Vy[i]!=0.0f)
			{
				cchek='y';
				break;
			}
		}
		if(cchek=='x')
		{
			j = updateCount_me(X,Y,coinCount);
			if(j == 0)//lost my chance
			{
				if(X[0]==2.0f)//striker goes into the hole,penalty:return pocketed white coin to board
				{
					l = position_replace(X,Y);//the positon to bring in penalty
					if(l==1) { x_r=0.0f;y_r=0.0f; }
					if(l==2) { x_r=-0.41f;y_r=0.0f; }
					if(l==3) { x_r=0.41f;y_r=0.0f; }
					if(l==4) { x_r=0.0f;y_r=-0.41f; }
					if(l==5) { x_r=0.0f;y_r=0.41f; }
					if(l==6) { x_r=-1.4f;y_r=-1.4f; }
					
					if(isRed_me == 'y')
					{
						X[5] = x_r;
						Y[5] = y_r;
						isInHole[5] = 'n';
						coinCount[2] = coinCount[2] - 1;
						isRed_me = 'n';
						score_4p[0]=score_4p[0]-3;
					}
					else if(X[3] == 2.0f)
					{
						X[3] = x_r;
						Y[3] = y_r;
						isInHole[3] = 'n';
						coinCount[1] = coinCount[1]-1;//chek
						score_4p[0]=score_4p[0]-2;
					}
					else if(X[4] == 2.0f)
					{
						X[4] = x_r;
						Y[4] = y_r;
						isInHole[4] = 'n';
						coinCount[1] = coinCount[1]-1;
						score_4p[0]=score_4p[0]-2;
					}
				}
				chance[3]='y';
				chance[0]='n';chance[1]='n';chance[2]='n';
				//appropriately give coordinates of striker
				y_of_str=0.0f;
				while(1)
				{
					if(present_b4(1.275f,y_of_str) == 1) break;
					y_of_str = y_of_str+0.2f;
				}
				X[0]=1.275f;
				Y[0]=y_of_str;
				dir = 'n';
			}
			if(j == 1)
			{
				chance[0]='n';chance[1]='n';chance[3]='n';
				chance[2]='y';
				//appropriately give coordinates of striker
				x_of_str=0.0f;
				while(1)
				{
					if(present_b4(x_of_str,-1.275f) == 1) break;
					x_of_str = x_of_str+0.2f;
				}
				X[0]=x_of_str;
				Y[0]=-1.275f;
				dir = 'y';
			}
			
			isStrikerHitByMe='n';
			isStrikerHitByOther='n';
			isInHole[0]='n';
			alpha=0;
			//printf("@@check@@ Vx[0]=%f Vy[0]=%f\n",Vx[0],Vy[0]);
		}
	}
	if(isStrikerHitByOther=='y' && chance[2]=='n')//yahan pe aa rha h jo aana nahi chahiye
	{
		for(i=0;i<6;i++)
		{
			if(Vx[i]!=0.0f || Vy[i]!=0.0f)
			{
				cchek='y';
				break;
			}
		}
		if(cchek=='x')
		{
			k = updateCount_other(X,Y,coinCount);
			if(k == 0)
			{
				if(X[0]==2.0f)//striker goes into the hole,penalty:return pocketed black coin to board
				{
					l = position_replace(X,Y);//the positon to bring in penalty
					if(l==1) { x_r=0.0f;y_r=0.0f; }
					if(l==2) { x_r=-0.41f;y_r=0.0f; }
					if(l==3) { x_r=0.41f;y_r=0.0f; }
					if(l==4) { x_r=0.0f;y_r=-0.41f; }
					if(l==5) { x_r=0.0f;y_r=0.41f; }
					if(l==6) { x_r=-1.4f;y_r=-1.4f; }
					
					if(chance[1]=='y' || chance[3]=='y')
					{
						if(isRed_other == 'y')
						{
							X[5] = x_r;
							Y[5] = y_r;
							isInHole[5] = 'n';
							coinCount[2] = coinCount[2] - 1;
							isRed_other = 'n';
							score_4p[1]=score_4p[1]-3;
						}
						else if(X[1] == 2.0f)
						{
							X[1] = x_r;
							Y[1] = y_r;
							isInHole[1] = 'n';
							coinCount[0] = coinCount[0]-1;//chek
							score_4p[1]=score_4p[1]-2;
						}
						else if(X[2] == 2.0f)
						{
							X[2] = x_r;
							Y[2] = y_r;
							isInHole[2] = 'n';
							coinCount[0] = coinCount[0]-1;
							score_4p[1]=score_4p[1]-2;
						}
					}
					if(chance[0]=='y')
					{
						if(isRed_me == 'y')
						{
							X[5] = x_r;
							Y[5] = y_r;
							isInHole[5] = 'n';
							coinCount[2] = coinCount[2] - 1;
							isRed_me = 'n';
							score_4p[0]=score_4p[0]-3;
						}
						else if(X[3] == 2.0f)
						{	
							X[3] = x_r;
							Y[3] = y_r;
							isInHole[3] = 'n';
							coinCount[1] = coinCount[1]-1;//chek
							score_4p[0]=score_4p[0]-2;
						}
						else if(X[4] == 2.0f)
						{
							X[4] = x_r;
							Y[4] = y_r;
							isInHole[4] = 'n';
							coinCount[1] = coinCount[1]-1;
							score_4p[0]=score_4p[0]-2;
						}
					}
				}
				//giving chance to other needs to be done carefully
				if(chance[0]=='y')
				{	
					chance[1]='y';
					chance[0]='n';chance[2]='n';chance[3]='n';
					//will have to give coordinates of striker here
					y_of_str=0.0f;
					while(1)
					{
						if(present_b4(-1.275f,y_of_str) == 1) break;
						y_of_str = y_of_str-0.2f;
					}
					X[0]=-1.275f;
					Y[0]=y_of_str;
				}
				else if(chance[1]=='y')
				{	
					chance[2]='y';
					chance[0]='n';chance[1]='n';chance[3]='n';
					//will have to give coordinates of striker here
					x_of_str=0.0f;
					while(1)
					{
						if(present_b4(x_of_str,-1.275f) == 1) break;
						x_of_str = x_of_str+0.2f;
					}
					X[0]=x_of_str;
					Y[0]=-1.275f;
				}
				else if(chance[3]=='y')
				{	
					chance[0]='y';
					chance[1]='n';chance[2]='n';chance[3]='n';
					//will have to give coordinates of striker here
					x_of_str=0.0f;
					while(1)
					{
						if(present_b4(x_of_str,1.275f) == 1) break;
						x_of_str = x_of_str-0.2f;
					}
					X[0]=x_of_str;
					Y[0]=1.275f;
				}
				dir = 'y';
				
			}
			if(k == 1)
			{
				if(chance[0]=='y')
				{	
					chance[0]='y';
					chance[1]='n';chance[2]='n';chance[3]='n';
					//will have to give coordinates of striker here
					x_of_str=0.0f;
					while(1)
					{
						if(present_b4(x_of_str,1.275f) == 1) break;
						x_of_str = x_of_str-0.2f;
					}
					X[0]=x_of_str;
					Y[0]=1.275f;
				}
				else if(chance[1]=='y')
				{	
					chance[1]='y';
					chance[0]='n';chance[2]='n';chance[3]='n';
					//will have to give coordinates of striker here
					y_of_str=0.0f;
					while(1)
					{
						if(present_b4(-1.275f,y_of_str) == 1) break;
						y_of_str = y_of_str-0.2f;
					}
					X[0]=-1.275f;
					Y[0]=y_of_str;
				}
				else if(chance[3]=='y')
				{	
					chance[3]='y';
					chance[0]='n';chance[1]='n';chance[2]='n';
					//will have to give coordinates of striker here
					y_of_str=0.0f;
					while(1)
					{
						if(present_b4(1.275f,y_of_str) == 1) break;
						y_of_str = y_of_str+0.2f;
					}
					X[0]=1.275f;
					Y[0]=y_of_str;
				}
				dir = 'n';
			}
			isStrikerHitByOther='n';
			isStrikerHitByMe='n';
			isInHole[0]='n';
			alpha=0;
			
		}
	}
}


