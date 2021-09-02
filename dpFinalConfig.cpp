#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<map>
#include<windows.h>
#include<iterator>
#include<utility>
#include<set>
#include<math.h>
#include<string>

using namespace std;


void showSetPairsInt(set<pair<int,int> > s,string title);

void lineToEdges(int root,vector<int> line,set<pair<int,int> > &granted,set<pair<int,int> > &forbidden)
{
    int n = line.size();
    //cout<<"Line size is : "<<n<<endl;

    granted.insert(make_pair(root,line.at(0)));
    if(n > 1)
    {

        for(int i=1;i<n;i++)
        forbidden.insert(make_pair(root,line.at(i)));

        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if(j-i == 1)
                    granted.insert(make_pair(line.at(i),line.at(j)));
                else
                    forbidden.insert(make_pair(line.at(i),line.at(j)));
            }
        }
    }

    //showSetPairsInt(granted,"temp : Granted");
    //showSetPairsInt(forbidden,"temp : Forbidden");
}

void showVecInt(vector<int> v)
{
    vector<int> :: iterator i;
    for(i = v.begin();i!=v.end();i++)
        cout<<*i<<" ";
    cout<<endl;
}

pair<int,int> revPair(pair<int,int> p)
{
    return make_pair(p.second,p.first);
}

void showSetPairsInt(set<pair<int,int> > s,string title)
{
    cout<<title<<" : "<<endl;
    set<pair<int,int> > :: iterator i;
    for(i = s.begin();i!=s.end();i++)
    {
        pair<int,int> temp = *i;
        cout<<"( "<<temp.first<<" , "<<temp.second<<" )"<<endl;
    }
}

void showPair(pair<int,int> p)
{
    cout<<"( "<<p.first<<" , "<<p.second<<" )";
}

bool isXInVec(int x,vector<int> vec)
{
    for(int i=0;i<vec.size();i++)
    {
        if(vec.at(i) == x)
            return true;
    }
return false;
}


class config{

  public :
  int n; //number of lines
  int root;
  vector<int> *lines;
  set<pair<int,int> > granted;
  set<pair<int,int> > forbidden;

      config(int n1,int root1)
      {
          n = n1;
          root = root1;
          lines = new vector<int>[n];
      }

      config()
      {
         //for empty call of the object
      }

      void addNodeInLine(int line_no,int node)
      {
          lines[line_no].push_back(node);
      }

      void setGrantedAndForbidden()
      {
          vector<int> temp;
          for(int i=0;i<n;i++)
          {
              temp = lines[i];
              //cout<<"The Encountered Line is : "<<endl;
              //showVecInt(temp);
              lineToEdges(root,temp,granted,forbidden);
          }
      }

      int numOfVertices()
      {
          int count = 0;
          for(int i = 0;i<n;i++)
            count += lines[i].size();

       return (count + 1);
      }

      void printConfig()
      {
          cout<<"root : "<<root<<endl;
          for(int i=0;i<n;i++)
          {
              cout<<"Line "<<i + 1<<" : ";
              showVecInt(lines[i]);
          }
      }


      vector<vector<int> > getLines()
      {
          vector<vector<int> > outlines;
          for(int i=0;i<n;i++)
          {
              vector<int> temp;
              temp.push_back(root);

              for(int j=0;j<lines[i].size();j++)
                temp.push_back(lines[i].at(j));



              outlines.push_back(temp);
          }
        return outlines;
      }

      vector<int> genOrder(vector<int> vec)
      {
          vector<int> res;

         for(int i=0;i<vec.size();i++)
         {
             if(vec.at(i) != root)
             {
                 for(int j=0;j<n;j++)
                 {
                     if(isXInVec(vec.at(i),lines[j]))
                     {
                         res.push_back(j);
                         break;
                     }
                   //lines loop
                 }
             }
          //vector loop
         }



      return res;
      }


      //implement another function to check if the config is the last config of this category

      void printConfigToFile(std :: ofstream &fout)
      {
          fout<<"ROOT : "<<root<<endl<<endl;
          for(int i = 0;i<n;i++)
          {
              fout<<"Line"<<i+1<<" : ";
              for(int j=0;j<lines[i].size();j++)
              {
                  fout<<lines[i].at(j)<<" ";
              }
              fout<<endl;
          }
         fout<<"---------------------------------------"<<endl;
      }
      void printConfigFull()
      {
          cout<<"root : "<<root<<endl;
          for(int i=0;i<n;i++)
          {
              cout<<"Line "<<i + 1<<" : ";
              showVecInt(lines[i]);
          }

          showSetPairsInt(granted,"Granted Edges");
          showSetPairsInt(forbidden,"\n Forbidden Edges");
      }

};


bool areConfigsSame(config c,config d)
{
    map<vector<int>,int> mp;
    vector<vector<int> > contC = c.getLines();
    vector<vector<int> > contD = d.getLines();

    for(int i=0;i<contC.size();i++)
    {
        mp[contC.at(i)]++;
    }

    for(int i=0;i<contD.size();i++)
    {
        mp[contD.at(i)]++;
    }


    map<vector<int>,int> :: iterator it;

    for(it = mp.begin();it!=mp.end();it++)
    {
        int x = it->second;

        if(x!=2)
         return false;

    }

return true;
}
//if they are same, returns true, else false




void printConfigVecToFile(vector<config> v,std :: ofstream &fout)
{
    fout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    config temp;
    for(int i=0;i<v.size();i++)
    {
        temp = v.at(i);
        temp.printConfigToFile(fout);
    }
    fout<<"***************************************"<<endl;
}

bool isCompatible(config c1,config c2)
{
    cout<<"Compatibility check"<<endl;

    set<pair<int,int> > granted1 = c1.granted;
    set<pair<int,int> > granted2 = c2.granted;
    set<pair<int,int> > forbidden1 = c1.forbidden;
    set<pair<int,int> > forbidden2 = c2.forbidden;

    //cout<<"\n\nChecking if compatible or not"<<endl;

    set<pair<int,int> > :: iterator i;
    pair<int,int> temp;

    for(i = granted1.begin();i!= granted1.end();i++)
    {
        temp = *i;
        if(forbidden2.find(temp)!=forbidden2.end() || forbidden2.find(revPair(temp))!=forbidden2.end())
        {
            //showPair(temp);
            //cout<<"is in granted1 but found in forbidden1"<<endl;
            //cout<<"Not Compatible\n";
            return false;
        }
    }

    for(i = granted2.begin();i!= granted2.end();i++)
    {
        temp = *i;
        if(forbidden1.find(temp)!=forbidden1.end() || forbidden1.find(revPair(temp))!=forbidden1.end())
        {
            //showPair(temp);
            //cout<<"is in granted2 but found in forbidden1"<<endl;
            //cout<<"Not Compatible\n";
            return false;
        }
    }

    for(i = forbidden1.begin();i!= forbidden1.end();i++)
    {
        temp = *i;
        if(granted2.find(temp)!=granted2.end() || granted2.find(revPair(temp))!=granted2.end())
        {
            //showPair(temp);
            //cout<<"is in forbidden1 but found in granted2"<<endl;
            //cout<<"Not Compatible\n";
            return false;
        }
    }

    for(i = forbidden2.begin();i!= forbidden2.end();i++)
    {
        temp = *i;
        if(granted1.find(temp)!=granted1.end() || granted1.find(revPair(temp))!=granted1.end())
        {
            //showPair(temp);
            //cout<<"is in forbidden2 but found in granted1"<<endl;
            //cout<<"Not Compatible\n";
            return false;
        }
    }

//cout<<"They are compatible"<<endl;
return true;
}

bool isAllCompatible(config con[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(isCompatible(con[i],con[j]) == false)
               return false;
        }
    }

 return true;
}

bool isAllCompatibleWith(vector<config> branch,config temp)
{
    int n = branch.size();
    for(int i=0;i<n;i++)
    {
        if(isCompatible(branch.at(i),temp) == false)
            {
                cout<<"CONFIGURATION IS NOT COMPATIBLE WITH THE VECTOR"<<endl;
                cout<<"-----------------------------------------------------"<<endl;
                return false;
            }
    }
cout<<"CONFIGURATION IS COMPATIBLE WITH THE VECTOR"<<endl;
cout<<"-----------------------------------------------------"<<endl;
return true;
}


bool isAllCompatibleWithInPlace(vector<config> branch,config temp)
{
    int n = branch.size();
    for(int i=0;i<n;i++)
    {
        if(isCompatible(branch.at(i),temp) == false && branch.at(i).root < temp.root)
            {
                cout<<"CONFIGURATION IS NOT COMPATIBLE WITH THE VECTOR"<<endl;
                cout<<"-----------------------------------------------------"<<endl;
                return false;
            }
    }
cout<<"CONFIGURATION IS COMPATIBLE WITH THE VECTOR"<<endl;
cout<<"-----------------------------------------------------"<<endl;
return true;

}

//copied from divider new module
void showVecOfVecInt1(vector<vector<int> > arr);

void swapVecElt(vector<int> &v,int i,int j)
{
    int temp = v.at(i);
    v.at(i) = v.at(j);
    v.at(j) = temp;
}

void permute(vector<vector<int> > &container,vector<int> &arr,int start,int end)
{
    if(start == end)
    {
        container.push_back(arr);
    }

    int i;

    for(i = start;i<=end;i++)
    {
        swapVecElt(arr,i,start);
        permute(container,arr,start + 1,end);
        swapVecElt(arr,i,start);
    }
}

vector<vector<int> > permutationGenerator(vector<int> arr)
{
    vector<vector<int> > container;
    int start = 0;
    int end = arr.size() - 1;

    permute(container,arr,start,end);


cout<<"permuted patterns"<<endl;
cout<<"-----------------------------"<<endl;
showVecOfVecInt1(container);




return container;
}

vector<int> sortVec(vector<int> v)
{
    int n = v.size();
    vector<int> temp = v;
    int c;

    for(int i=0;i<n;i++)
    {
        for(int j = i+1;j<n;j++)
        {
            if(temp.at(j) < temp.at(i))
            {
                c = temp.at(i);
                temp.at(i) = temp.at(j);
                temp.at(j) = c;
            }
        }
    }
return temp;
}

void partitionCreatorUtil(vector<int> arr,map<vector<int>,int> &finalCont)
{
    vector<int> newArr = sortVec(arr);

    if(0 < newArr.at(0) && finalCont[newArr] < 1)
    {
        finalCont[newArr]++;
    }

    if(arr.at(0) == 1)
    {
        cout<<"Termination"<<endl;
    }
    else
    {
        arr[0] = arr[0] - 1;

        for(int i=1;i<arr.size();i++)
        {
            arr[i]++;
            partitionCreatorUtil(arr,finalCont);
            arr[i]--;
        }
    }

}

//n is the number of vertex and k is the line number
int maxOfVec(vector<int> v)
{
    int temp = -1;

    for(int i=0;i<v.size();i++)
    {
        if(temp < v.at(i))
            temp = v.at(i);
    }
return temp;
}

vector<vector<int> > filterByPointBound(vector<vector<int> > v,int bound)
{
    vector<vector<int> > cont;

    for(int i=0;i<v.size();i++)
    {
        if(maxOfVec(v.at(i)) > bound)
        {
            cout<<"Exceeded"<<endl;
        }
        else
        {
            cont.push_back(v.at(i));
        }
    }

return cont;
}


//n is the number of vertex and k is the line number
vector<vector<int> > partitionCreator(int n,int k,int point_bound)
{

    vector<int>  arr;
    arr.push_back(n-k+1);

    if(k > 1)
    {
        for(int i=0;i<k-1;i++)
        {
            arr.push_back(1);
        }
    }

    map<vector<int>,int> finalCont;

    partitionCreatorUtil(arr,finalCont);

    vector<vector<int> > outCont;
    map<vector<int>,int> :: iterator it;
    for(it = finalCont.begin();it!=finalCont.end();it++)
    {
        vector<int> temp = it->first;
        outCont.push_back(temp);
    }


    outCont = filterByPointBound(outCont,point_bound);

 return outCont;
}



//any match found then return true, that means config already present in the container
bool checkExistenceOfConfig(vector<config> cont,config c)
{
    for(int i=0;i<cont.size();i++)
    {
        if(areConfigsSame(c,cont.at(i)) == true)
            return true;
    }
return false;
}






config configFromEltsAndPartition(int root,vector<int> elts,vector<int> part)
{
    cout<<"creating config from a part and given elts"<<endl;

    int line_num = part.size();
    int k = 0;
    config temp(line_num,root);

    for(int i=0;i<part.size();i++)
    {
        //line index i

        for(int j=0;j<part.at(i);j++)
        {
            temp.addNodeInLine(i,elts.at(k));
            k++;
        }
    }
    temp.setGrantedAndForbidden();

return temp;
}


vector<config> configsOfPartition(int root,vector<vector<int> > permutedVecs,vector<int> part)
{
    //inside partition creator

    cout<<"configs of a given partition with the permuted elts provided"<<endl;

    vector<config> cons;

    for(int i=0;i<permutedVecs.size();i++)
    {
        vector<int> elts = permutedVecs.at(i);
        config tempCon = configFromEltsAndPartition(root,elts,part);
        //PUT THEM AFTER PASSING THROUGH THE CONTENT FILTER
        if(checkExistenceOfConfig(cons,tempCon) == false)
        {
            cons.push_back(tempCon);
        }
    }
return cons;
}

void insertChildVecToMother(vector<config> &mother,vector<config> child)
{
    for(int i=0;i<child.size();i++)
    {
        mother.push_back(child.at(i));
    }
}


vector<config> configOfLineNumAndRootWithElts(int root,vector<vector<int> > permutedVecs,int line_num,int point_bound)
{
    cout<<"function of generating all configs of a given line num , permuted vecs and root "<<endl;

    int n = permutedVecs.at(0).size();
    int k = line_num;
    vector<vector<int> > parts = partitionCreator(n,k,point_bound);
    vector<config> mother;

    for(int i=0;i<parts.size();i++)
    {
       vector<config> child = configsOfPartition(root,permutedVecs,parts.at(i));
       insertChildVecToMother(mother,child);
    }

return mother;
}


vector<vector<config> > configOfRootWithElts(int root,vector<vector<int> > permutedVecs,int point_bound)
{
    cout<<"function of generating all configs of a given n with the provided permuted elts"<<endl;

    int n = permutedVecs.at(0).size();
    // now we know line numbers vary from 1 to n
    // we had a misconception about point bound and getting line number from that
    int q = n/point_bound;
    int r = n%point_bound;

    if(r!=0)
     q = q + 1;

    //start is q alright, but only those partitions are allowed whose max length line is of the point bound capacity

    int start = q;

    vector<vector<config> > cons;
    //each row consists of all the configs of a given line num

    //if unit line configs are considered 1st, they have a low chance to appear to be contradictory, so we are reversing config generation, from highest line count to lowest possible
    for(int line_num = start;line_num <= n;line_num++)
    {
        vector<config> confTemp = configOfLineNumAndRootWithElts(root,permutedVecs,line_num,point_bound);
        cons.push_back(confTemp);
    }

return cons;
}

vector<vector<config> > configOfRootWithN(int root,int n,int point_bound)
{
    cout<<"function of generating all configs of a given n = "<<n<<endl;

    vector<int> arr;
    for(int i=0;i<n;i++)
    {
        if(i!=root)
        {
            arr.push_back(i);
        }
    }

    vector<vector<int> > permutedVecs;

    if(root == 0)
    {
        //since no permutation for the case of root == 0
        permutedVecs.push_back(arr);
    }
    else
    {
        permutedVecs = permutationGenerator(arr);
    }

    vector<vector<config> > cons = configOfRootWithElts(root,permutedVecs,point_bound);


return cons;
}

vector<vector<vector<config> > > allConfigGenWithN(int n,int point_bound)
{
    vector<vector<vector<config> > > cons;

    for(int root = 0;root<n-1;root++)
    {
        vector<vector<config> > confTemp = configOfRootWithN(root,n,point_bound);
        cons.push_back(confTemp);
    }

return cons;
}








//copied from collinear program

vector<int> subVec(vector<int> v,int start,int end)
{
    vector<int> output;
    for(int i = start;i<=end;i++)
    {
        output.push_back(v.at(i));
    }
return output;
}

bool compareVec(vector<int> v1,vector<int> v2) //suppose sizes are equal
{
    if(v1.size()!= v2.size())
      return false;

    for(int i=0;i<v1.size();i++)
    {
        if(v1.at(i) != v2.at(i))
            return false;
    }
return true;
}

/*
void showVec(vector<int> v)
{
    for(int i=0;i<v.size();i++)
      cout<<v.at(i)<<",";

}*/


//subset filter

bool isContinuousSubArray(vector<int> mother,vector<int> child)
{
    /*cout<<"cont subarray called for: "<<endl;
    showVecInt(mother);
    cout<<" and ";
    showVecInt(child);*/


    if(mother.size() < child.size())
        {
            //cout<<"container vector is of less size"<<endl;
            return false;
        }

    int startPt = 0;
    int endPt = child.size() - 1;

    while(endPt < mother.size())
    {
        vector<int> temp = subVec(mother,startPt,endPt);
        if(compareVec(temp,child) == true)
         {
             //showVec(temp);
             //cout<<" is present in : ";
             //showVec(mother);
             //cout<<endl;
             return true;
         }
        else
        {
            startPt++;
            endPt++;
        }
    }

//cout<<"No match found"<<endl;
return false;
}

vector<int> revVecInt(vector<int> v)
{
    vector<int> vecout;
    for(int i = v.size()-1;0<=i;i--)
    {
        vecout.push_back(v.at(i));
    }
return vecout;
}



bool isContinuousSubsetOfAny(vector<int> vec,set<vector<int> > motherSet)
{
    vector<int> revVec = revVecInt(vec);
    //cout<<"cont subset check called"<<endl;
    set<vector<int> > :: iterator it;
    for(it = motherSet.begin();it!=motherSet.end();it++)
    {
        vector<int> temp = *it;

        if(isContinuousSubArray(temp,vec) && (vec.size()<temp.size()))
            return true;

        if(isContinuousSubArray(temp,revVec) && (revVec.size()<temp.size()))
            return true;
    }
 return false;
}








set<vector<int> > subsetFilter(set<vector<int> > motherSet)
{
    //cout<<"SUBSETFILTER CALLED"<<endl;
    set<vector<int> > outputSet;
    set<vector<int> > :: iterator it;
    for(it = motherSet.begin();it!=motherSet.end();it++)
    {
        vector<int> temp = *it;
        if(isContinuousSubsetOfAny(temp,motherSet) == false)
            outputSet.insert(temp);
    }
return outputSet;
}


//subset filter ends


//coupling filter
int checkIntersection(vector<int> firstVec,vector<int> secondVec)
{
    /*
    cout<<"debug code: "<<endl;
    showVecInt(firstVec);
    cout<<" and ";
    showVecInt(secondVec);
    cout<<" are getting checked"<<endl;
    */



    int k1 = firstVec.size();
    int k2 = secondVec.size();
    int startPt,endPt;

    if(k1<k2)
    {
        startPt = 0; //its end k1 -1
        endPt = k1 - 1; // its start 0
    }
    else if(k2<k1)
    {
        startPt = k1 - k2;
        endPt = k2 - 1;
    }
    else
    {
        startPt = 0;
        endPt = k2 - 1;
    }


    while(startPt < k1)
    {
        vector<int> temp1 = subVec(firstVec,startPt,k1-1);
        vector<int> temp2 = subVec(secondVec,0,endPt);

        if(compareVec(temp1,temp2) == true)
        {
            /*showVecInt(temp1);
            cout<<" : in the intersected portion of";
            showVecInt(firstVec);
            cout<<" and ";
            showVecInt(secondVec);
            cout<<endl;*/
            return temp1.size();
        }
        else
        {
            startPt++;
            endPt--;
        }

    }

/*cout<<"no intersection"<<endl;*/
return 0;
}

vector<int> lineCouple(vector<int> firstVec,vector<int> secondVec,int k) //k denotes the common portion length
{

    /*showVecInt(firstVec);
    cout<<" is coupled with : ";
    showVecInt(secondVec);
    cout<<" at k: "<<k<<endl;*/


    vector<int> temp = firstVec;
    for(int i=k;i<secondVec.size();i++)
    {
        temp.push_back(secondVec.at(i));
    }
return temp;
}

bool checkDup(vector<int> v)
{
    map<int,int> mp;
    for(int i=0;i<v.size();i++)
    {
        mp[v.at(i)]++;
    }

    map<int,int> :: iterator it;
    for(it = mp.begin();it!=mp.end();it++)
    {
        //cout<<it->first<<" count : "<<it->second<<endl;
        if(it->second > 1)
        return true;

    }
 return false;
}



//couples every possible vectors between those two sets
//also keeping the subsets
set<vector<int> > couplingFilter(set<vector<int> > mother,vector<vector<int> > child)
{
    set<vector<int> > :: iterator it;

    for(int i=0;i<child.size();i++)
    {
        for(it=mother.begin();it!=mother.end();it++)
        {
            vector<int> temp = *it;
            vector<int> revTemp = revVecInt(temp);//reverse the vector temp
            vector<int> current = child.at(i);
            vector<int> revCurrent = revVecInt(current);//reverse the current vector

            //pairs
            //temp,curr ---> both sides
            //temp,Revcurr ---> both sides
            //revtemp,curr ---> both sides
            //revtemp,revcurr ---> both sides


            //1st step

            int k1 = checkIntersection(temp,current);


            if(k1>1)
            {
                vector<int> res1 = lineCouple(temp,current,k1);

                if(checkDup(res1) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res1);
                 }
            }

            int k2 = checkIntersection(current,temp);

            if(k2>1)
            {
                vector<int> res2 = lineCouple(current,temp,k2);

                if(checkDup(res2) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res2);
                 }
            }


            //2nd step

             k1 = checkIntersection(temp,revCurrent);


            if(k1>1)
            {
                vector<int> res1 = lineCouple(temp,revCurrent,k1);

                if(checkDup(res1) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res1);
                 }
            }


            k2 = checkIntersection(revCurrent,temp);
            if(k2>1)
            {
                vector<int> res2 = lineCouple(revCurrent,temp,k2);

                if(checkDup(res2) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res2);
                 }
            }

            //3rd step

            k1 = checkIntersection(revTemp,current);


            if(k1>1)
            {
                vector<int> res1 = lineCouple(revTemp,current,k1);

                if(checkDup(res1) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res1);
                 }
            }

            k2 = checkIntersection(current,revTemp);
            if(k2>1)
            {
                vector<int> res2 = lineCouple(current,revTemp,k2);

                if(checkDup(res2) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res2);
                 }
            }

            //4th step

            k1 = checkIntersection(revTemp,revCurrent);


            if(k1>1)
            {
                vector<int> res1 = lineCouple(revTemp,revCurrent,k1);

                if(checkDup(res1) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res1);
                 }
            }



            k2 = checkIntersection(revCurrent,revTemp);
            if(k2>1)
            {
                vector<int> res2 = lineCouple(revCurrent,revTemp,k2);

                if(checkDup(res2) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res2);
                 }
            }


        //loop patch ends

        }

     mother.insert(child.at(i));
    }

return mother;
}



set<vector<int> > couplingFilterForOrders(set<vector<int> > mother,vector<vector<int> > child)
{
    set<vector<int> > :: iterator it;

    for(int i=0;i<child.size();i++)
    {
        for(it=mother.begin();it!=mother.end();it++)
        {
            vector<int> temp = *it;
            //vector<int> revTemp = revVecInt(temp);//reverse the vector temp
            vector<int> current = child.at(i);
            //vector<int> revCurrent = revVecInt(current);//reverse the current vector

            //pairs
            //temp,curr ---> both sides
            //temp,Revcurr ---> both sides
            //revtemp,curr ---> both sides
            //revtemp,revcurr ---> both sides


            //1st step

            int k1 = checkIntersection(temp,current);


            if(k1>1)
            {
                vector<int> res1 = lineCouple(temp,current,k1);

                if(checkDup(res1) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res1);
                 }
            }

            int k2 = checkIntersection(current,temp);

            if(k2>1)
            {
                vector<int> res2 = lineCouple(current,temp,k2);

                if(checkDup(res2) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res2);
                 }
            }


            /*
            //2nd step

             k1 = checkIntersection(temp,revCurrent);


            if(k1>1)
            {
                vector<int> res1 = lineCouple(temp,revCurrent,k1);

                if(checkDup(res1) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res1);
                 }
            }


            k2 = checkIntersection(revCurrent,temp);
            if(k2>1)
            {
                vector<int> res2 = lineCouple(revCurrent,temp,k2);

                if(checkDup(res2) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res2);
                 }
            }

            //3rd step

            k1 = checkIntersection(revTemp,current);


            if(k1>1)
            {
                vector<int> res1 = lineCouple(revTemp,current,k1);

                if(checkDup(res1) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res1);
                 }
            }

            k2 = checkIntersection(current,revTemp);
            if(k2>1)
            {
                vector<int> res2 = lineCouple(current,revTemp,k2);

                if(checkDup(res2) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res2);
                 }
            }

            //4th step

            k1 = checkIntersection(revTemp,revCurrent);


            if(k1>1)
            {
                vector<int> res1 = lineCouple(revTemp,revCurrent,k1);

                if(checkDup(res1) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res1);
                 }
            }



            k2 = checkIntersection(revCurrent,revTemp);
            if(k2>1)
            {
                vector<int> res2 = lineCouple(revCurrent,revTemp,k2);

                if(checkDup(res2) == false)
                 {
                     //cout<<"No rept, pushed"<<endl;
                     mother.insert(res2);
                 }
            }
           */

        //loop patch ends

        }

     mother.insert(child.at(i));
    }

return mother;
}





int getMin(int a,int b)
{
    if(a<b)
     return a;
return b;
}



// it will be in collinear program file
// this is the contradiction filter
//if content intersection is more than 1,in the final collinear components, then the pattern is contradictory
int contentIntersection(vector<int> vec1,vector<int> vec2)
{
    map<int,int> mp1;
    map<int,int> mp2;

    for(int i=0;i<vec1.size();i++)
    {
        mp1[vec1.at(i)]++;
    }

    for(int i=0;i<vec2.size();i++)
    {
        mp2[vec2.at(i)]++;
    }


    map<int,int> :: iterator it1,it2;


    int count = 0;

    for(it1 = mp1.begin();it1!=mp1.end();it1++)
    {
        for(it2 = mp2.begin();it2!=mp2.end();it2++)
        {
            if(it1->first == it2->first)
            {
                count = count + getMin(it1->second,it2->second);
            }

         //iterator loop patch end
        }
    }


return count;
}

bool contradictoryFilter(set<vector<int> > motherSet)
{
    vector<vector<int> > colComps;
    set<vector<int> > :: iterator it;

    for(it = motherSet.begin();it!=motherSet.end();it++)
    {
        vector<int> temp = *it;
        colComps.push_back(temp);
    }


    for(int i=0;i<colComps.size();i++)
    {
        for(int j=i+1;j<colComps.size();j++)
        {
            if(contentIntersection(colComps.at(i),colComps.at(j)) > 1)
            {
                return true;
            }

         //iterator loop patch end
        }
    }

return false;
}

set<vector<int> > couplingFilterOnBranch(vector<config> branch)
{
    set<vector<int> > outset;

    for(int i=0;i<branch.size();i++)
    {
        vector<vector<int> > tempLines = branch.at(i).getLines();

        if(i == 0)
        {
            for(int j=0;j<tempLines.size();j++)
                outset.insert(tempLines.at(j));
        }
        else
        {
            outset = couplingFilter(outset,tempLines);
        }
    }

    return outset;
}

void showSetVecInt(set<vector<int> > lineSet);

bool searchCommutativity(vector<int> child,set<vector<int> > motherSet)
{
    //cout<<"-------------------------------------------"<<endl;
    //cout<<"search comm called between: "<<endl;

    //cout<<"set:"<<endl;
    //showSetVecInt(motherSet);

    //cout<<" and childVector: ";
    //showVecInt(child);





    set<vector<int> > :: iterator it;
    for(it = motherSet.begin();it!=motherSet.end();it++)
    {
        vector<int> temp = *it;
        vector<int> revTemp = revVecInt(temp);

        if(compareVec(temp,child) == true || compareVec(revTemp,child) == true)
        {
            //cout<<"finished, found"<<endl;
            //cout<<"-----------------------------------------"<<endl;
            return true;
        }
    }

 //cout<<"finished, not found"<<endl;
 //cout<<"-----------------------------------------"<<endl;
 return false;
}



set<vector<int> > commutativityFilter(set<vector<int> > motherSet)
{
    //cout<<"COMMUTATIVITY FILTER CALLED"<<endl;

    set<vector<int> > outSet;
    set<vector<int> > :: iterator it;

    for(it = motherSet.begin();it!=motherSet.end();it++)
    {
        vector<int> temp = *it;
        if(searchCommutativity(temp,outSet) == false)
        {
            outSet.insert(temp);
        }
    }

return outSet;
}


void showVec(vector<int> v)
{
    for(int i=0;i<v.size();i++)
      cout<<v.at(i)<<",";
}



set<vector<int> > collinearComps(vector<config> branch)
{
    //coupling filter
    //commutativity filter
    //subset filter

    set<vector<int> > temp = couplingFilterOnBranch(branch);
    temp = commutativityFilter(temp);
    temp = subsetFilter(temp);

return temp;
}




//copying from the collinear module ends here
void showSetVecInt(set<vector<int> > lineset)
{
    set<vector<int> > :: iterator it;
    for(it = lineset.begin();it!=lineset.end();it++)
    {
        vector<int> temp = *it;
        showVecInt(temp);
        cout<<endl;
    }
}


int posCount(int arr[],int n)
{
    int count = 0;
    for(int i=0;i<n;i++)
    {
        if(arr[i]>=0)
            count++;
    }
return count;
}

int negCount(int arr[],int n)
{
    int count = 0;
    for(int i=0;i<n;i++)
    {
        if(arr[i]<0)
            count++;
    }
return count;
}


bool isPosInc(int arr[],int n)
{
    int k = posCount(arr,n);
    int brr[k];
    int m = 0;
    for(int i=0;i<n;i++)
    {
        if(arr[i]>=0)
        {
            brr[m] = arr[i];
            m++;
        }
    }

    for(int i=0;i<k-1;i++)
    {
        if(brr[i]>brr[i+1])
            return false;
    }
return true;
}

bool isNegDec(int arr[],int n)
{
    int k = negCount(arr,n);
    int brr[k];
    int m = 0;
    for(int i=0;i<n;i++)
    {
        if(arr[i]<0)
        {
            brr[m] = arr[i];
            m++;
        }
    }

    for(int i=0;i<k-1;i++)
    {
        if(brr[i]<brr[i+1])
            return false;
    }
return true;
}

bool noNegRepeat(int arr[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        if(arr[i]<0 && arr[i+1]<0)
            return false;
    }
return true;
}

void printConfigVec(vector<config> branch)
{
    vector<config> :: iterator i = branch.begin();
    int pattern_no = 1;
    while(i!=branch.end())
    {
        cout<<"Pattern No : "<<pattern_no<<endl;
        config temp = *i;
        temp.printConfig();
        i++;
        pattern_no++;
    }

}

void emptyVector(vector<config> &branch)
{
    while(!branch.empty())
        branch.pop_back();
    cout<<"Vector is Emptied"<<endl;
}


void inplaceEmptyVector(vector<config> &branch,int level)
{
    int size = branch.size();

    if(size <= level + 1)
    {
        //directly insert
        //nothing to empty
    }
    else{

        int k = size - level - 1;

        for(int i = 0;i<k;i++)
        {
            branch.pop_back();
        }
    }
}

void inplacePush(vector<config> &branch,int level,config temp)
{
    int size = branch.size();

    if(level + 1 <= size)
    {
        int k = size - level;

        for(int i = 0;i<k;i++)
        {
            branch.pop_back();
        }

    }

    branch.push_back(temp);



}


//copied from allCliques module

vector<int> toBin1(int x)
{
  vector<int> arr;
  while(x>0)
  {
      arr.push_back(x%2);
      x = x/2;
  }
  return arr;
}

void showVec1(vector<int> arr)
{
    vector<int> :: iterator it;
    cout<<"The vector is : ";
    for(it = arr.begin();it!=arr.end();it++)
    {
        cout<<*it<<" ,";
    }
    cout<<endl;
}

void updateValue(vector<int> &a)
{
    a[1] = 15;
}


void toBinUpdateVec1(int x,vector<int> &arr)
{
    int i=0;
    while(x>0)
    {
        arr[i] = x%2;
        i++;
        x = x/2;
    }
}

vector<vector<int> > toBinToX(int x,int len)
{
    vector<vector<int> > res;
    for(int i=1;i<=x;i++)
    {
        vector<int> temp;

        for(int j=0;j<len;j++)
        {
            temp.push_back(0);
        }

        toBinUpdateVec1(i,temp);
        res.push_back(temp);
    }
   return res;
}

void showVecOfVecInt1(vector<vector<int> > arr)
{
    vector<vector<int> > :: iterator it1;

    for(it1 = arr.begin();it1!=arr.end();it1++)
    {
        vector<int> temp = *it1;
        vector<int> :: iterator it2;
        for(it2 = temp.begin();it2 != temp.end();it2++)
        {
            cout<<*it2<<" ";
        }
        cout<<endl;
    }
}

vector<int> generateSubset(vector<int> setArr,vector<int> binArr)
{
    vector<int> res;

    for(int i=0;i<binArr.size();i++)
    {
        if(binArr[i] == 1)
        {
            res.push_back(setArr[i]);
        }

    }
return res;
}



vector<vector<int> > generateAllSubset(vector<int> setArr)
{
    int len = setArr.size();
    int x = pow(2,len) - 1;
    vector<vector<int> > finalRes;
    vector<vector<int> > res = toBinToX(x,len);
    vector<vector<int> > :: iterator it;

    for(it = res.begin();it!=res.end();it++)
    {
        vector<int> temp = *it;
        //temp is acting here as the bin array of the prev func argument
        finalRes.push_back(generateSubset(setArr,temp));
    }
return finalRes;
}

bool findValue1(vector<int> arr,int x)
{
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i] == x)
            return true;
    }
return false;
}


class graph{

   int V;
   vector<int> *adj;

   public :

       graph(int V1)
       {
           V = V1;
           adj = new vector<int>[V];
       }

       void addEdge(int v,int w)
       {
           adj[v].push_back(w);
           adj[w].push_back(v);
       }

       bool isEdge(int v,int w) // later on we have to declare it as a member function of graph class
      {
         //vector<int> :: iterator it1 = ;
         //vector<int> :: iterator it2 = ;

            if(findValue1(adj[v],w) && findValue1(adj[w],v))
            {
                return true;
            }
        return false;
      }

      vector<int> vertexSet()
      {
          vector<int> res;
          for(int i=0;i<V;i++)
          {
              res.push_back(i);
          }
       return res;
      }

      void showGraph()
      {
          for(int i=0;i<V;i++)
          {
              cout<<"vertex : "<<i<<"-->";
              showVec1(adj[i]);
          }
      }


};


bool isClique(vector<int> setArr,graph g)
{
    for(int i=0;i<setArr.size();i++)
    {
        for(int j=i+1;j<setArr.size();j++)
        {
            if(g.isEdge(setArr[i],setArr[j]) == false)
                return false;
        }
    }

return true;
}

vector<vector<int> > allCliques(graph g)
{
    vector<int> setArr = g.vertexSet();
    vector<vector<int> > allSubs = generateAllSubset(setArr);
    vector<vector<int> > :: iterator it;
    vector<vector<int> > finalSet;


    for(it = allSubs.begin();it!=allSubs.end();it++)
    {
        vector<int> temp = *it;
        if(temp.size() > 2 && isClique(temp,g))
        {
            finalSet.push_back(temp);
        }

    }
return finalSet;
}

vector<int> maxClique(graph g)
{
    vector<vector<int> > cliques = allCliques(g);
    vector<int> temp;
    int tempLen = 0;

    for(int i=0;i<cliques.size();i++)
    {
        if(cliques.at(i).size() > tempLen)
        {
            temp = cliques.at(i);
            tempLen = cliques.at(i).size();
        }
    }

 return temp;
}

int maxCliqueLength(graph g)
{
    vector<int> temp = maxClique(g);
return temp.size();
}

//end of copying


//suppose square matrix in entered, so we are not writing the code to check whether it is square or not
bool isSymmetric(vector<vector<int> > adjMat)
{
    int n = adjMat.size();

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(adjMat.at(i).at(j) != adjMat.at(j).at(i))
            {
                return false;
            }

          //iterator loop patch end here
        }
    }
return true;
}


graph matrixToGraph(vector<vector<int> > adjMat)
{
        int n = adjMat.size();
        graph g(n);

        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if(adjMat.at(i).at(j) == 1)
                {
                    g.addEdge(i,j);
                }

                //iterator loop ends here
            }
        }
     //symmetric check ends here
     return g;
}

void emptyVector111(vector<config> &branch)
{
    int n = branch.size();
    for(int i=0;i<n-1;i++)
     branch.pop_back();
    cout<<"Vector is Emptied"<<endl;
}

bool isDec(int arr[],int n)
{
    for(int i=1;i<n;i++)
    {
        if(arr[i-1]<arr[i])
            return false;
    }
return true;
}

bool isInc(int arr[],int n)
{
    for(int i=1;i<n;i++)
    {
        if(arr[i-1]>arr[i])
            return false;
    }
return true;
}

void bubbleSort(int *arr,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(arr[j]<arr[i])
                swap(arr[i],arr[j]);
        }
    }
}

void printArr(int arr[],int n)
{
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

bool nextPerm(int arr[],int n)
{
    if(isDec(arr,n))
    {
        //printArr(arr,n);
        return false;
    }

    if(isInc(arr,n))
    {
        swap(arr[n-1],arr[n-2]);
        //printArr(arr,n);
        return true;
    }

    int index1;
    for(int i=n-2;i>=0;i--)
    {
        if(arr[i]<arr[i+1])
        {
            index1 = i;
            break;
        }
    }

    int index2;
    int min = arr[index1 + 1];
    for(int i=index1 + 1;i<n;i++)
    {
        if(arr[index1] < arr[i] && arr[i]<=min)
        {
            index2 = i;
            min = arr[i];
        }
    }

    swap(arr[index1],arr[index2]);

    for(int i = index1 + 1;i<n;i++)
    {
        for(int j = i+1;j<n;j++)
        {
            if(arr[j]<arr[i])
                swap(arr[i],arr[j]);
        }
    }

return true;
}


void printVecOfVecInt(vector<vector<int> > mat)
{
    vector<vector<int> > :: iterator it;
    for(it = mat.begin();it!=mat.end();it++)
    {
        vector<int> temp = *it;
        for(int i=0;i<temp.size();i++)
        {
            cout<<temp.at(i)<<" ";
        }
        cout<<endl;
    }
}

void printVecOfVecIntToFile(vector<vector<int> > mat,std :: ofstream &fout)
{
    fout<<"-------------------------------"<<endl;
    vector<vector<int> > :: iterator it;
    for(it = mat.begin();it!=mat.end();it++)
    {
        vector<int> temp = *it;
        for(int i=0;i<temp.size();i++)
        {
            fout<<temp.at(i)<<" ";
        }
        fout<<endl;
    }
    fout<<"---------------------------------"<<endl;
}


void printVecToFile(vector<int> vec,std :: ofstream &fout)
{
    for(int i=0;i < vec.size();i++)
    {
        fout<<vec.at(i)<<" ,";
    }
    fout<<endl;
}

void printSetOfVecIntToFile(set<vector<int> > motherSet,std :: ofstream &fout)
{
    set<vector<int> > :: iterator it;

    for(it = motherSet.begin();it!=motherSet.end();it++)
    {
        vector<int> temp = *it;
        printVecToFile(temp,fout);
    }
}


void configToMatrixFill(config c,vector<vector<int> > &mat)
{
    set<pair<int,int> > :: iterator it1;

    for(it1 = c.granted.begin();it1 != c.granted.end();it1++)
    {
        pair<int,int> temp = *it1;
        mat[temp.first][temp.second] = 1;
        mat[temp.second][temp.first] = 1;
    }

    for(it1 = c.forbidden.begin();it1 != c.forbidden.end();it1++)
    {
        pair<int,int> temp = *it1;
        mat[temp.first][temp.second] = 0;
        mat[temp.second][temp.first] = 0;
    }

}


vector<vector<int> > branchToMatrix(vector<config> branch)
{
    config c = branch.at(0);
    int n = c.numOfVertices();
    vector<int> decoy;
    vector<vector<int> > mat;

    for(int i=0;i<n;i++)
        decoy.push_back(-1);

    for(int i=0;i<n;i++)
        mat.push_back(decoy);

    vector<config> :: iterator it;
    for(int i=0;i<branch.size();i++)
    {
       configToMatrixFill(branch.at(i),mat);
       printVecOfVecInt(mat);
       cout<<"-----------------------------------------"<<endl;
    }

    //yet to implement
    return mat;
}



vector<int> maxLine(set<vector<int> > colComps)
{
    vector<int> tempVec;
    int temp = 0;

    set<vector<int> > :: iterator it;

    for(it = colComps.begin();it!=colComps.end();it++)
    {
        vector<int> c = *it;
        if(temp < c.size())
        {
            temp = c.size();
            tempVec = c;
        }
    }
return tempVec;
}

//no need to worry about the size, square matrix is being entered
bool isMatrixFullForGraph(vector<vector<int> > mat)
{
    int n = mat.at(0).size();

    for(int i=0;i<n;i++)
    {
        for(int j = i+1;j<n;j++)
        {
            if(mat.at(i).at(j) == -1)
                return false;
        }
    }

return true;
}




//PATTERN ORDER CHECKING MODULE

bool searchEltInVec(vector<int> vec,int x)
{
    for(int i=0;i<vec.size();i++)
    {
        if(vec.at(i) == x)
         return true;
    }
return false;
}

bool isEqualVecs(vector<int> vec1,vector<int> vec2)
{
    if(vec1.size()!= vec2.size())
     return false;

    for(int i=0;i<vec1.size();i++)
    {
        if(vec1.at(i) != vec2.at(i))
         return false;
    }

return true;
}


bool isRevVecs(vector<int> vec1,vector<int> vec2)
{
    if(vec1.size()!= vec2.size())
     return false;

    int n = vec1.size();
    for(int i=0;i<n;i++)
    {
        if(vec1.at(i) != vec2.at(n - 1 - i))
         return false;
    }

return true;
}


//considering each vector does not have any repetitions
//checking what two vectors with all distinct elements are in common, are they also in same order
//if so, returns true, else false
//see, clearly, intersection more than size 2 are only realevent

//we wont be needing this method for now, this not gonna work
bool orderOfIntersectionMatchCheck(vector<int> arr,vector<int> brr)
{
    map<int,int> mp;

    for(int i=0;i<arr.size();i++)
    {
        mp[arr.at(i)]++;
    }

    for(int i=0;i<brr.size();i++)
    {
        mp[brr.at(i)]++;
    }

    map<int,int> :: iterator it;

    vector<int> intersect;

    for(it = mp.begin();it!=mp.end();it++)
    {
        if(it->second > 1)
            intersect.push_back(it->first);
    }

    if(intersect.size() < 3)
    {
        //no point in order compatibility checking
        return true;
    }
    else
    {
        vector<int> vec1;
        vector<int> vec2;

        for(int i=0;i<arr.size();i++)
        {
            if(searchEltInVec(intersect,arr.at(i)))
             vec1.push_back(arr.at(i));
        }

        for(int i=0;i<brr.size();i++)
        {
            if(searchEltInVec(intersect,brr.at(i)))
             vec2.push_back(brr.at(i));
        }

        if(isEqualVecs(vec1,vec2) || isRevVecs(vec1,vec2))
        {
            return true;
        }
    }

 return false;
}

bool isEltIsolatedInVec(vector<int> vec,int x)
{
    int n = vec.size();

    if(vec.at(0) == x && vec.at(1) != x)
     return true;

    if(vec.at(n-1) == x && vec.at(n-2) != x)
     return true;


     for(int i = 1;i<n-1;i++)
     {
         if(vec.at(i) == x && (vec.at(i-1) != x && vec.at(i+1) != x))
          return true;

     }

return false;
}

//1st checks if there itself there is any ripple or knot in the ordering, is so, that is discarded by this check
//if not, then the order is passed to check the compatibility with other orders
bool isOrderValid(vector<int> vec)
{
    map<int,int> mp;

    for(int i=0;i<vec.size();i++)
    {
        mp[vec.at(i)]++;
    }

    map<int,int> :: iterator it;

    for(it = mp.begin();it!=mp.end();it++)
    {
        //if the element is repeated and isolated, then invalid ordering
        if(it->second > 1 && isEltIsolatedInVec(vec,it->first))
         {
             //debug code
             cout<<"The order: ";
             showVecInt(vec);
             cout<<" is not valid as "<<it->first<<" is repeated in isolated manner"<<endl;

             return false;
         }
    }

cout<<"Order";
showVecInt(vec);
cout<<" is valid"<<endl;

return true;
}

//this function extracts the order in form where there is no repetitions
//so that we can directly use it for finding order mismatch with other orders of this sort
//one thing to mention, only two extracted orders can go for mis match checking
//one extracted and one not, it wont cut it

//this will be applied only on those, whose ordering is valid, but repetition is there
vector<int> extractOrder(vector<int> vec)
{
    vector<int> outCont;

    for(int i=0;i<vec.size();i++)
    {
        if(searchEltInVec(outCont,vec.at(i)) == false)
         outCont.push_back(vec.at(i));
    }


//debug code
cout<<"=============================="<<endl;
cout<<"The extracted order from :";
showVecInt(vec);
cout<<"is : ";
showVecInt(outCont);
cout<<endl;
cout<<"=============================="<<endl;
//debug code ends

return outCont;
}

//one un-extracted order of length 3 or more and one set of extracted orders are the arguments
//the unextracted order will be checked first, if it is valid or not, if not valid, return false, there
//else the order will be extracted and then will be matched with the set orders
// if mismatch found then return false there, else if not suborder of any, then insert in the set
//checking this part will cost us some more runtime, probably the subset filter
// or else, we can keep them all for now.

//actually order compatibility checking has its loop hole so, we need to follow the path traversing approach
//1st function unit path generator: arguments start,end, set of orders
//path generator: arguments order, set of orders, the order is extracted
//check path function
//path direction function

int indexOfEltInVec(int x,vector<int> vec)
{
    for(int i=0;i<vec.size();i++)
    {
        if(vec.at(i) == x)
          return i;
    }
return -1;
}



int unitPathGenerator(int start,int end,set<vector<int> > orders)
{
    set<vector<int> > :: iterator it;

    for(it = orders.begin();it!=orders.end();it++)
    {
        vector<int> temp = *it;
        int startIndex = indexOfEltInVec(start,temp);
        int endIndex = indexOfEltInVec(end,temp);

        if(startIndex != -1 && endIndex != -1)
        {
            if(startIndex < endIndex)
             {
                 return 1;
             }

             if(startIndex > endIndex)
             {
                 return -1;
             }

        }

    }

return 0;
}


vector<int> pathGenerator(vector<int> ord,set<vector<int> > orders)
{
    int n = ord.size();
    vector<int> pathOut;

    for(int i=0;i<n-1;i++)
    {
        int c = unitPathGenerator(ord.at(i),ord.at(i+1),orders);
        pathOut.push_back(c);
    }

//debug code
cout<<"--------------------------------"<<endl;
cout<<"path of ";
showVecInt(ord);
cout<<" with respect to : "<<endl;
cout<<"*****************************"<<endl;
showSetVecInt(orders);
cout<<"*****************************"<<endl;
cout<<"is: ";
showVecInt(pathOut);
cout<<endl;
cout<<"--------------------------------"<<endl;
//debug code ends


return pathOut;
}

bool isPathValid(vector<int> path)
{
    map<int,int> mp;

    for(int i=0;i<path.size();i++)
    {
        mp[path.at(i)]++;
    }

    if(mp[1] > 0 && mp[-1] > 0)
    {
        //both direction exists

        cout<<"The path ";
        showVecInt(path);
        cout<<" is not valid"<<endl;

        return false;
    }


    cout<<"The path ";
    showVecInt(path);
    cout<<" is valid"<<endl;

return true;
}


//assuming only valid path are passed here as an argument
int getOrientationOfPath(vector<int> path)
{
    map<int,int> mp;

    for(int i=0;i<path.size();i++)
    {
        mp[path.at(i)]++;
    }

    //neutral and forward directions only
    if(mp[1] > 0)
     {
         cout<<"The path ";
        showVecInt(path);
        cout<<" has forward orientation"<<endl;
         return 1;
     }

    //neutral and backward directions only
    if(mp[-1] > 0)
     {
        cout<<"The path ";
        showVecInt(path);
        cout<<" has backward orientation"<<endl;
        return -1;
     }

    //neutral directions only
    if(mp[1] == 0 && mp[-1] == 0)
     {
        cout<<"The path ";
        showVecInt(path);
        cout<<" has neutral orientation"<<endl;
        return 0;
     }

//wont come to this. but to complete the definition
return 0;
}

vector<int> reverseVecInt(vector<int> v)
{
    vector<int> outVec;
    int n = v.size();

    for(int i = n-1;0<=i;i--)
    {
        outVec.push_back(v.at(i));
    }

return outVec;
}


bool isInSet(set<vector<int> > orders,vector<int> ord)
{
    set<vector<int> > :: iterator it;

    for(it = orders.begin();it!=orders.end();it++)
    {
        vector<int> temp = *it;
        if(isEqualVecs(temp,ord))
          return true;
    }
return false;
}



//only checks for path orientation
//valid or invalid, that should be checked before
bool checkOrder(vector<int> ord,set<vector<int> > &orders)
{

        if(orders.empty())
        {
            orders.insert(ord);
            return true;
        }

        if(isInSet(orders,ord))
        {
            cout<<"Already present, so do nothing"<<endl;
            return true;
        }

        //after that create path based on the set
        //check path, if path is contradictory, return false
        //if path is ok, turn the order into forward span and push it into the set
        vector<int> path = pathGenerator(ord,orders);
        if(isPathValid(path) == false)
        {
            return false;
        }
        else
        {
            int direction = getOrientationOfPath(path);

            if(direction == -1)
            {
               ord = reverseVecInt(ord);
               //ord will be inserted following coupling and subset filter
               vector<vector<int> > child;
               child.push_back(ord);
               orders = couplingFilterForOrders(orders,child);
               //orders = subsetFilter(orders);


               //orders.insert(ord);
            }
            else if(direction == 0)
            {
                cout<<"Neutral order will not be inserted"<<endl;
            }
            else
            {
                //ord will be inserted following coupling and subset filter
               vector<vector<int> > child;
               child.push_back(ord);
               orders = couplingFilterForOrders(orders,child);
               //orders = subsetFilter(orders);

            }

            return true;
        }


//although it will never come to this, still for the functions validity
return true;
}

set<vector<int> > setSubtract(set<vector<int> > mother,set<vector<int> > child)
{
    set<vector<int> > :: iterator it;
    set<vector<int> > res;
    for(it = mother.begin();it!=mother.end();it++)
    {
        vector<int> temp = *it;
        vector<int> revTemp = reverseVecInt(temp);

        if(isInSet(child,temp) == false && isInSet(child,revTemp) == false)
        {
            res.insert(temp);
        }
    }

return res;
}



//process order set, and fill order components
//direct generate all the orders of a collinear component with respect to a config, and push it into this
//only valid orders and order with length 3 and onward will be in orders
bool fillOrderComponent(set<vector<int> > orders)
{
    set<vector<int> > ordComps;
    int compSize = 0;

    do
    {
        compSize = ordComps.size();
        set<vector<int> > :: iterator it;

        for(it = orders.begin();it!=orders.end();it++)
        {
           vector<int> temp = *it;
           if(checkOrder(temp,ordComps) == false)
            return false;
        }

        //debug code
        cout<<"Order Component"<<endl;
        showSetVecInt(ordComps);
        cout<<endl;
        //debug code ends

    }
    while(compSize!=ordComps.size());

    if(ordComps.size() < orders.size())
    {
        cout<<"There are some spare neutrals"<<endl;
        //there can be another formation components between those neutrals as well
        //so pass those neutrals once again through the same function
        //return fillOrders : arg is orders minus ordComps

        set<vector<int> > remained = setSubtract(orders,ordComps);

        cout<<"spare neutrals are: "<<endl;
        showSetVecInt(remained);
        cout<<"passed again in the component checking"<<endl;

        return fillOrderComponent(remained);
    }

return true;
}


//orders consists of all the unrefined orders
//all the refined should be filled in valid orders.thats y pointer is passed
//in between is false. returned, then altogether false,, and the valid set is of no use
//ps: only valid order with length 3 or more will be pushed
bool validOrderFilter(set<vector<int> > orders,set<vector<int> > &validOrders)
{
    set<vector<int> > :: iterator it;
    for(it = orders.begin();it!=orders.end();it++)
    {
        vector<int> temp = *it;
        if(isOrderValid(temp) == false)
        {
            return false;
        }
        else
        {
            temp = extractOrder(temp);
            if(temp.size() > 2)
            {
                validOrders.insert(temp);
            }
        }

    }

return true;
}

//argument is unrefined, orders, directly generated out of a config and the set of cl comps
bool orientationFilter(set<vector<int> > orders)
{
    //debug code
    cout<<"unrefined orders of collinear Components : "<<endl;
    showSetVecInt(orders);
    cout<<endl;
    //debug code ends

    set<vector<int> > validOrders;
    if(validOrderFilter(orders,validOrders) == false)
    {
        return false;
    }

    if(validOrders.empty())
     return true; // that means all orders are of length 2, so no restrictions


return fillOrderComponent(validOrders);
}

//now all that is left is to implement order generator with respect to a config
// that can only be done in the main module

bool orientationFilterForAConfig(config c,set<vector<int> > colComps)
{
    //debug code
    cout<<"Col Comps are : "<<endl;
    showSetVecInt(colComps);
    cout<<endl;
    //debug code ends

    set<vector<int> > :: iterator it;
    set<vector<int> > crudeOrders;

    for(it = colComps.begin();it!=colComps.end();it++)
    {
        vector<int> temp = *it;

        if(temp.size() > 2)
        {
            vector<int> ord = c.genOrder(temp);

            //debug code
            cout<<"Order of: ";
            showVecInt(temp);
            cout<<"is ";
            showVecInt(ord);
            cout<<endl;
            //debug code ends

            if(ord.size() > 2)
                crudeOrders.insert(ord);
        }
    }

    if(crudeOrders.empty())
    {
        cout<<"no orders there to process wrt this config";
        return true;
    }


   return orientationFilter(crudeOrders);
}

bool orientationFilterOfBranchConfig(vector<config> branch,set<vector<int> > colComps)
{
    for(int i=0;i<branch.size();i++)
    {
        if(orientationFilterForAConfig(branch.at(i),colComps) == false)
         return false;
    }

return true;
}






//END OF THE DIRECTIONAL MODULE











//if printFlag is 1, then allowed to print it in the file,if 0, not allowed
bool allFilter(vector<config> branch,int L,int K,std :: ofstream &fout,std :: ofstream &foutm,map<set<vector<int> >,int> &allcolComps)
{
    //contradictory filter
    //collinearity filter (including every filter helped to get collinear components)
    //clique filter


    int n = branch.at(0).numOfVertices();

    printConfigVec(branch);
    vector<vector<int> > mat = branchToMatrix(branch);

    //alllines is the container of the collinear component here
    set<vector<int> > alllines = collinearComps(branch);

    cout<<"COLLINEAR COMPONENTS: "<<endl;
    showSetVecInt(alllines);

    //printing into file
    /*fout<<endl<<endl;
    fout<<"BRANCH OF COMPATIBLE VECTORS"<<endl;
    printConfigVecToFile(branch,fout);
    fout<<"Adj Matrix : "<<endl;
    printVecOfVecIntToFile(mat,fout);
    fout<<"Collinear Components: "<<endl;
    printSetOfVecIntToFile(alllines,fout);*/

    if(contradictoryFilter(alllines) == true)
    {
        //fout<<"Primary Line Contradiction Occurs"<<endl;
        //fout<<"So, not Extending Further"<<endl;
        return false;
    }

    //not line contradictory if passed the previous test

    int l = maxLine(alllines).size();
    if(l > 0 && (L < l || l == L))
    {
        if(branch.size() < n-1)
        {
            cout<<"Not Extending"<<endl;
            //fout<<"Max collinearity reached, l = "<<l<<endl;
            //fout<<"So, not Extending Further"<<endl;
        }
        return false;
    }

    //collinearity is below the bound if passed the previous test

    graph g = matrixToGraph(mat);
    vector<int> maxC = maxClique(g);
    int k = maxC.size();
    if(0 < k && (K < k || k == K))
    {
        //fout<<"Clique reached to the max size, max-clique is: ";
        //printVecToFile(maxC,fout);
        //cout<<endl;

        if(branch.size() < n-1)
        {
            cout<<"Not Extending"<<endl;
            //fout<<"Max Clique reached, k = "<<k<<endl;
            //fout<<"So, not Extending Further"<<endl;
        }
        return false;
    }

    //clique size is below bound if passed the previous test

    if(orientationFilterOfBranchConfig(branch,alllines) == false)
    {
        if(branch.size() < n-1)
        {
            cout<<"Not Extending"<<endl;
            //fout<<"Secondary Orientation Contradiction Occurs"<<endl;
            //fout<<"So, not Extending Further"<<endl;
        }
        return false;
    }

    //somewhat drawable if passed the previous test

    //if matrix is full then check from there are no need to extend further

    if(isMatrixFullForGraph(mat) == true && branch.size() < n-1)
    {
        if(allcolComps[alllines]<1)
        {
            allcolComps[alllines]++;
            foutm<<"*******************************************************"<<endl;
            foutm<<"BRANCH OF COMPATIBLE VECTORS"<<endl;
            printConfigVecToFile(branch,foutm);
            foutm<<"-------------------------------------------------------"<<endl;
            foutm<<"Adj Matrix : "<<endl;
            printVecOfVecIntToFile(mat,foutm);
            foutm<<"-------------------------------------------------------"<<endl;
            foutm<<"Collinear Components: "<<endl;
            printSetOfVecIntToFile(alllines,foutm);
            foutm<<"-------------------------------------------------------"<<endl;

            if(k>0)
            {
                foutm<<"Max Clique: ";
                printVecToFile(maxC,foutm);
            }
            else
            {
                foutm<<"No Clique over size 2 exists to Consider"<<endl;
            }
            foutm<<"_______________________________________________________________"<<endl;
            foutm<<" l = "<<l<<" and k = "<<k<<endl;
        }

      return false; //since that branch will not extend further
    }





    //if the traversal is reached to the leaf and yet its a ok pattern that means it got through the clique and collinearity
    //so apart from the generic flow of the traversal, we need to check them ourselves

    if(branch.size() == n-1)
    {
        if(allcolComps[alllines]<1)
        {
            allcolComps[alllines]++;
            foutm<<"*******************************************************"<<endl;
            foutm<<"BRANCH OF COMPATIBLE VECTORS"<<endl;
            printConfigVecToFile(branch,foutm);
            foutm<<"-------------------------------------------------------"<<endl;
            foutm<<"Adj Matrix : "<<endl;
            printVecOfVecIntToFile(mat,foutm);
            foutm<<"-------------------------------------------------------"<<endl;
            foutm<<"Collinear Components: "<<endl;
            printSetOfVecIntToFile(alllines,foutm);
            foutm<<"-------------------------------------------------------"<<endl;

            if(k>0)
            {
                foutm<<"Max Clique: ";
                printVecToFile(maxC,foutm);
            }
            else
            {
                foutm<<"No Clique over size 2 exists to Consider"<<endl;
            }
            foutm<<"_______________________________________________________________"<<endl;
            foutm<<" l = "<<l<<" and k = "<<k<<endl;
        }

    }

    //fout<<"Pattern OK"<<endl;
    return true;
}



vector<config> configGeneratorByRootAndLine(int root,int line_num,int n)
{
    int size = n + line_num - 1;
    int arr[size];
    int k = 0;

    for(int i=0;i<n;i++)
    {
        if(i!=root)
        {
            arr[k] = i;
            k++;
        }
    }

    int divider = -1;

    for(int i = k;i<size;i++)
    {
        arr[i] = divider;
        divider--;
    }

    bubbleSort(arr,size);
    bool flag = true;
    vector<config> cons;

    while(flag)
    {
        printArr(arr,size);
        cout<<"------------------------------------------"<<endl;

        if(root == 0)
        {
            if(isNegDec(arr,size) && isPosInc(arr,size) && noNegRepeat(arr,size) && arr[0] == -1 && arr[size - 1]>0)
            {
                cout<<"Pattern Found"<<endl;
                printArr(arr,size);
                //Sleep(2000);
                config temp(line_num,root);
                int line_index = -1;
                for(int i =0;i<size;i++)
                {
                    if(arr[i]<0)
                        line_index++;
                    else
                        temp.addNodeInLine(line_index,arr[i]);
                }
                temp.setGrantedAndForbidden();
                cons.push_back(temp);

            }
        }
        else
        {
            if(isNegDec(arr,size) && isPosInc(arr,size) && noNegRepeat(arr,size) && arr[0] == -1 && arr[size - 1]>0)
            {
                cout<<"Pattern Found"<<endl;
                printArr(arr,size);
                //Sleep(2000);
                config temp(line_num,root);
                int line_index = -1;
                for(int i =0;i<size;i++)
                {
                    if(arr[i]<0)
                        line_index++;
                    else
                        temp.addNodeInLine(line_index,arr[i]);
                }
                temp.setGrantedAndForbidden();
                cons.push_back(temp);

            }

        }

        flag = nextPerm(arr,size);
    }

return cons;
}

vector<vector<config> >  configGeneratorByRoot(int root,int n)
{
    vector<vector<config> > cons;
    for(int line_num = 1;line_num<n;line_num++)
    {
        vector<config> temp = configGeneratorByRootAndLine(root,line_num,n);
        cons.push_back(temp);
    }
return cons;
}

vector<vector<vector<config> > > configGeneratorAll(int n)
{
    vector<vector<vector<config> > > cons;
    for(int root = 0;root<n - 1;root++)
    {
        vector<vector<config> > temp = configGeneratorByRoot(root,n);
        cons.push_back(temp);
    }
return cons;
}





void configDFSUtil(int root,int n,int L,int K,vector<config> &branch,std::ofstream &fout,std :: ofstream &foutm,vector<vector<vector<config> > > &allcons,map<set<vector<int> >,int> &allcolComps) //n is the number of vertices
{
    cout<<"Root : "<<root<<endl;
   // Sleep(2000);

   vector<vector<config> > cons = allcons.at(root);

   for(int i = 0;i<cons.size();i++)
   {
       vector<config> consTemp = cons.at(i); //consisting of all the configs of root and num of lines i
       for(int j=0;j<consTemp.size();j++)
       {
           config temp = consTemp.at(j);

           if(root == 0)
           {
               inplacePush(branch,root,temp);

               if(root == n-2)
                {
                    cout<<"TERMINATION ROOT ENCOUNTERED"<<endl;
                    cout<<"One Branch is Traversed\n";
                    cout<<"------------------------------------------"<<endl;

                    allFilter(branch,L,K,fout,foutm,allcolComps);


                    cout<<"Returning...."<<endl;
                    cout<<"*********************************************"<<endl;
                            //Sleep(2000);

                            //break;
                            //return;
                }
                else
                {

                    if(allFilter(branch,L,K,fout,foutm,allcolComps) == true) // if pattern ok, return true
                    {
                        cout<<"SINCE ROOT :"<<root<<" IS NOT : "<<n-1<<", So Proceeding..."<<endl;
                        configDFSUtil(root + 1,n,L,K,branch,fout,foutm,allcons,allcolComps);
                    }

                }
           }
           else //root not equals to zero
           {
               if(isAllCompatibleWithInPlace(branch,temp))  //here is a small mistake, compatibility will be checked upto the new override node
                {
                    cout<<"Compatible config Found"<<endl;
                    cout<<"---------------------------------------------------------------"<<endl;
                    cout<<"The Pushed config is : "<<endl;
                    temp.printConfig();
                    cout<<"---------------------------------------------------------------"<<endl;
                            //Sleep(2000);
                            //branch.push_back(temp);
                    inplacePush(branch,root,temp);

                    if(root == n-2)
                    {
                        cout<<"TERMINATION ROOT ENCOUNTERED"<<endl;
                        cout<<"One Branch is Traversed\n";
                        cout<<"------------------------------------------"<<endl;

                        allFilter(branch,L,K,fout,foutm,allcolComps);


                                //emptyVector(branch);
                        cout<<"Returning...."<<endl;
                        cout<<"*********************************************"<<endl;
                                //Sleep(2000);
                                //break;

                                //return;
                    }
                    else
                    {
                                //cout<<"SINCE ROOT :"<<root<<" IS NOT : "<<n-1<<", So Proceeding..."<<endl;
                                //level wise filter can be implemented here
                                //if fails in parameter then break



                        if(allFilter(branch,L,K,fout,foutm,allcolComps) == true) // if pattern ok, return true
                        {
                            cout<<"SINCE ROOT :"<<root<<" IS NOT : "<<n-1<<", So Proceeding..."<<endl;
                            configDFSUtil(root + 1,n,L,K,branch,fout,foutm,allcons,allcolComps);
                        }
                     }

            }
            else
            {

                temp.printConfig();
                cout<<"is not compatible with the branch , so going to the next configuration\n\n";
            }


            //else root not equals to zero ends
           }






           //iterator loop ends
       }

   }

}

void configDFS(int n,int L,int K,std :: ofstream &fout,std :: ofstream &foutm) // n is the number of vertices
{
    //l - 2 because if were l - 1, the lines will be of max length l and discarded anyway
    int point_bound = L - 2; // assuming L is never entered to be 1
    vector<vector<vector<config> > > allcons = allConfigGenWithN(n,point_bound);
    map<set<vector<int> >,int> allcolComps;


    int root = 0;
    vector<config> branch;
    configDFSUtil(root,n,L,K,branch,fout,foutm,allcons,allcolComps);
}


string numToString(int n)
{
    string s = "";
    while(n>0)
    {
         s = char(n%10 + 48) + s;
         n = n/10;
    }

return s;
}

//TEST SPACE

set<vector<int> > giveTestColComps()
{
    set<vector<int> > res;

    //0 1
    vector<int> v1;
    v1.push_back(0);
    v1.push_back(1);
    res.insert(v1);

    //0 2 3
    vector<int> v2;
    v2.push_back(0);
    v2.push_back(2);
    v2.push_back(3);
    res.insert(v2);

    //0 4 5
    vector<int> v3;
    v3.push_back(0);
    v3.push_back(4);
    v3.push_back(5);
    res.insert(v3);

    //0 6 7
    vector<int> v4;
    v4.push_back(0);
    v4.push_back(6);
    v4.push_back(7);
    res.insert(v4);

    //1 2 4
    vector<int> v5;
    v5.push_back(1);
    v5.push_back(2);
    v5.push_back(4);
    res.insert(v5);

    //1 3 6
    vector<int> v6;
    v6.push_back(1);
    v6.push_back(3);
    v6.push_back(6);
    res.insert(v6);

    //1 5 7
    vector<int> v7;
    v7.push_back(1);
    v7.push_back(5);
    v7.push_back(7);
    res.insert(v7);

    //2 6 5
    vector<int> v8;
    v8.push_back(2);
    v8.push_back(6);
    v8.push_back(5);
    res.insert(v8);

    //2 7
    vector<int> v9;
    v9.push_back(2);
    v9.push_back(7);
    res.insert(v9);

    //3 4 7
    vector<int> v10;
    v10.push_back(3);
    v10.push_back(4);
    v10.push_back(7);
    res.insert(v10);

    //3 5
    vector<int> v11;
    v11.push_back(3);
    v11.push_back(5);
    res.insert(v11);

    //4 6
    vector<int> v12;
    v12.push_back(4);
    v12.push_back(6);
    res.insert(v12);


return res;
}

set<vector<int> > giveAnotherTestColComps()
{
    set<vector<int> > res;

    //0 3 4
    vector<int> v1;
    v1.push_back(0);
    v1.push_back(3);
    v1.push_back(4);
    res.insert(v1);

    //0 5 6
    vector<int> v2;
    v2.push_back(0);
    v2.push_back(5);
    v2.push_back(6);
    res.insert(v2);

    //1 4 5
    vector<int> v3;
    v3.push_back(1);
    v3.push_back(4);
    v3.push_back(5);
    res.insert(v3);

    //2 1 3
    vector<int> v4;
    v4.push_back(2);
    v4.push_back(1);
    v4.push_back(3);
    res.insert(v4);

    //4 2 6
    vector<int> v5;
    v5.push_back(4);
    v5.push_back(2);
    v5.push_back(6);
    res.insert(v5);

    //2 4 5
    /*vector<int> v6;
    v6.push_back(2);
    v6.push_back(4);
    v6.push_back(5);
    res.insert(v6);

    //2 6
    vector<int> v7;
    v7.push_back(2);
    v7.push_back(6);
    //v7.push_back(7);
    res.insert(v7);

    //3 6
    vector<int> v8;
    v8.push_back(3);
    v8.push_back(6);
    //v8.push_back(5);
    res.insert(v8);

    //2 3
    vector<int> v9;
    v9.push_back(2);
    v9.push_back(3);
    res.insert(v9);*/

return res;
}






//END OF TEST SPACE

//driver code
int main()
{
    /*

    config c(4,0); //number of lines 3 and root 0
    c.addNodeInLine(0,1); // 1st co ordinate is the line number
    c.addNodeInLine(1,2);
    c.addNodeInLine(2,3);
    c.addNodeInLine(2,4);
    c.addNodeInLine(3,5);
    c.addNodeInLine(3,6);
    //c.addNodeInLine(3,7);
    //adding lines complete

    c.setGrantedAndForbidden();
    //setting up granted and forbidden edges

    cout<<"The config is : "<<endl;
    c.printConfig();

    set<vector<int> > colComps = giveAnotherTestColComps();

    bool flag = orientationFilterForAConfig(c,colComps);

    if(flag)
    {
        cout<<"Passed for this config"<<endl;
    }
    else
    {
        cout<<"orientation contradiction found for this config"<<endl;
    }


    /*vector<config> branch;
    branch.push_back(c);


    branchToMatrix(branch);








    /*config d(3,0);
    d.addNodeInLine(0,2);
    d.addNodeInLine(0,3);
    d.addNodeInLine(0,1);
    d.addNodeInLine(1,4);
    d.addNodeInLine(1,5);
    d.addNodeInLine(2,6);
    d.addNodeInLine(2,7);
    d.addNodeInLine(2,8);
    //adding lines complete

    d.setGrantedAndForbidden();
    //setting up ranted and for bidden edges
    d.printConfig();
    cout<<"Number of vertices : "<<d.numOfVertices()<<endl;

    isCompatible(c,d);*/



    int n,L,K;
    cout<<"Enter n : ";
    cin>>n;
    //string num = std :: to_string(n);

    cout<<"Enter the upper limit of clique and line(<= "<<n-1<<")"<<endl<<endl;
    cout<<"collinearity limit.....L = ";
    cin>>L;
    cout<<"max clique limit....K = ";
    cin>>K;

    //main code

    ofstream fout,foutm;
    string filename = "finalOutPutOfN" + numToString(n) + "L" + numToString(L) + "K" + numToString(K) + ".txt";
    string filename1 = "outPutUncheckedByFilterOfN" + numToString(n) + "L" + numToString(L) + "K" + numToString(K) + ".txt";



    fout.open(filename.c_str());
    foutm.open(filename1.c_str());

    fout<<"Running for n = "<<n<<endl;
    fout<<"The given collinearity bound: l = "<<L<<endl;
    fout<<"The given Clique Size Bound: k = "<<K<<endl;

    configDFS(n,L,K,fout,foutm);
    fout.close();
    foutm.close();
    //showContent(filename);



return 0;
}
