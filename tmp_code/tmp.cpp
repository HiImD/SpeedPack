void Pack2x4::init(){
    std::vector< std::vector<int>> something = Func::randUnion(2, 4);
    int n_fixed = something[2][0];

    //Sinh ngau nhien vi tri cac FixedBlock de parse vao UP
    std::vector<Func::Vector> toOtherSize;
    {
        std::vector< std::vector<int>> something_copy(something);
        int i0;
        int j0;
        
        for(int i = 0; i < n_fixed/2; i++){
            i0 = rand() % 2;
            j0 = rand() % 4;
            if(something_copy[i0][j0] != 0 && something_copy[i0][j0] != -1){
                
                toOtherSize.push_back(Func::Vector(i0, j0)); 
                something_copy[i0][j0] = 0;
            } else {
                i--;
            }
        }
    }
    
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            switch (something[i][j])
            {  
                case 0:
                    CreatNewBlock(OBJTYPE::PICKABLEBLOCK, i, j);
                    break;
                case 1:
                    CreatNewBlock(OBJTYPE::FIXEDBLOCK, i, j);
                    break;
                case 2:
                    CreatNewBlock(OBJTYPE::FIXEDBLOCK, i, j, 1, 2);
                    break;
                case -2:
                    CreatNewBlock(OBJTYPE::FIXEDBLOCK, i, j, 2, 1);
                    break;
                default:
                    break;
            }
            if(something[i][j] != 0 && something[i][j] != -1){
                parse(3, (FixedBlock* ) table[i][j], false);;
            }
        }
    }
    
    int i0 ;
    int j0 ;
    
    for(int i = 0; i < n_fixed/2; i++){
        i0 = rand() % 2;
        j0 = rand() % 4;
        if(something[i0][j0] != 0 && something[i0][j0] != -1){
            if(something[i0][j0] != 0 && something[i0][j0] != -1){
                parse(0, (FixedBlock*) table[i0][j0]);
                parse(2, (FixedBlock* ) table[i0][j0], false);
                
            }
            delete table[i0][j0];
            table[i0][j0] = NULL;
            switch (something[i0][j0])
            {  
                case 1:
                    CreatNewBlock(OBJTYPE::PICKABLEBLOCK, i0, j0, 1, 1, false);
                    something[i0][j0] = 0;
                    break;
                case 2:
                    CreatNewBlock(OBJTYPE::PICKABLEBLOCK, i0, j0, 1, 1, false);
                    something[i0][j0] = 0;
                    CreatNewBlock(OBJTYPE::PICKABLEBLOCK, i0, j0 + 1, 1, 1, false);
                    something[i0][j0 + 1] = 0;
                    break;
                case -2:
                    CreatNewBlock(OBJTYPE::PICKABLEBLOCK, i0, j0, 1, 1, false);
                    something[i0][j0] = 0;
                    CreatNewBlock(OBJTYPE::PICKABLEBLOCK, i0 + 1, j0, 1, 1, false);
                    something[i0 + 1][j0] = 0;
                    break;
                default:
                    break;
                
            }
            
        } else {
            i--;
        }
    } 
    origin = getTexture();    
}