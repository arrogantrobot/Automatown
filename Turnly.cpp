statsLocal* getLocal(int tileNum){
	statsLocal* s1;
	s1 = new statsLocal;
	int r = -2,num;
	int population,jobs,iDem,cDem,rDem,nearRoad;
	population = jobs = iDem = cDem = rDem = nearRoad = 0;
	Structure *sPtr;
	while(r<3){
		for(int i=0;i<LOCAL_AREA;i++)
		{
			num = ((((tileNum+(ROW_LENGTH*r))-2)+i))%(ROW_LENGTH*ROW_LENGTH);
			if(num<0)
			{
				num = (ROW_LENGTH*ROW_LENGTH)+num;
			}
			sPtr = (*tiles)[num]->getStructure();
			population += sPtr->population;
			jobs += sPtr->jobs;
			iDem += sPtr->industrialDemand;
			cDem += sPtr->commercialDemand;
			rDem += sPtr->residentialDemand;
			if(sPtr->type==4){
				nearRoad = 1;
			}
			//printf("s1->pop = %d\n",s1->population);
		}
		r++;
	}
	s1->population = population;
	s1->jobs = jobs;
	s1->iDem = iDem;
	s1->cDem = cDem;
	s1->rDem = rDem;
	s1->nearRoad = nearRoad;
	return s1;
}

bool commerceGrowth(statsLocal * sl, int i)
{
	bool answer=false,a,b,c,d,e,f;
	a = sl->population > C_MIN ;
	b = (*tiles)[i]->getCanChange();
	c = (*tiles)[i]->getStructure()->type!=RESIDENTIAL;
	d = (*tiles)[i]->getStructure()->type!=COMMERCIAL;
	e = a&&b;
	f = c&&d;
	answer = e&&(f||(d&&sl->population > C_MIN_B));
	return answer;
}

bool commerceDecay(statsLocal * sl, int i)
{
	bool answer=false,a,b,c,d,e,f;
	a = (sl->population + sl->jobs) < C_MIN ;
	b = (*tiles)[i]->getCanChange();
	c = sl->nearRoad ==0;
	d = (*tiles)[i]->getStructure()->type==COMMERCIAL;
	e = a||c;
	f = b&&d;
	answer = e&&f;
	return answer;
}

bool residentialGrowth(statsLocal * sl, int i)
{
	bool answer=false,a,b,c,d,e,f;
	a = sl->jobs > R_MIN ;
	b = (*tiles)[i]->getCanChange();
	c = (*tiles)[i]->getStructure()->type!=RESIDENTIAL;
	d = (*tiles)[i]->getStructure()->type!=COMMERCIAL;
	e = a&&b;
	f = c&&d;
	answer = e&&f;
	return answer;
}

bool residentialDecay(statsLocal * sl, int i)
{
	bool answer=false,a,b,c,d,e,f;
	a = sl->jobs < R_MIN ;
	b = (*tiles)[i]->getCanChange();
	c = (*tiles)[i]->getStructure()->type==RESIDENTIAL;
	d = (*tiles)[i]->getStructure()->type!=COMMERCIAL;
	e = b&&c;
	f = e&&a;
	answer = f;
	return answer;
}

gint advanceTime(gpointer data)
{
	statsLocal * sl;
	std::list<change *> changes;
	printf("Calling advanceTime()\n");
    for(int i=0;i<(ROW_LENGTH*ROW_LENGTH);i++)
    {
    	sl = getLocal(i);
    	
    	if(commerceGrowth(sl,i))
    	{
    		if(sl->nearRoad){
				change *c;
				c = new change;
				c->location = i;
				c->structure = rand()%2+5;
				changes.push_back(c);
			}
		}else if(commerceDecay(sl,i))
		{
			change *c;
			c = new change;
			c->location = i;
			c->structure = rand()%3+12;
			changes.push_back(c);		
		}
    	if(residentialGrowth(sl,i))
    	{
    		change *c;
    		c = new change;
    		c->location = i;
    		c->structure = rand()%5;
    		changes.push_back(c);
		}/*else if(residentialDecay(sl,i))
    	{
    		change *c;
    		c = new change;
    		c->location = i;
    		c->structure = rand()%3+12;
    		changes.push_back(c);
		}  */  

		delete sl; 
    }
    if(!changes.empty())
    {
    	while(!changes.empty())
    	{
			changeTileTo(changes.front()->location,changes.front()->structure);
			changes.pop_front();
		}    		
    	drawTiles(buf2);
    	updateStats();
    }else{
    	printf("no changes\n");
    }
    printf("done advancing time\n");
    return 1;
}

void updateStats()
{
	std::string pop;
	std::ostringstream ss;
	pop = "Population: \t";
	printf("population updated to : %d\n",gameStats->getTotalPop());
	ss << gameStats->getTotalPop();
	pop.append(ss.str().c_str());
	gtk_label_set_text(GTK_LABEL(population),pop.c_str());
}
