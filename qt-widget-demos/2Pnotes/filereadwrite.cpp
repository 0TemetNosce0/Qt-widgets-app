//This file contains the fileoperation functions of the
// Application 2Pnotes 2.0.5

//It is included at the top of the file pbase.cpp

char* pbase::readfile(const QString& path, int* l)
{
    //read the file path, return the contents
    //int l returns the number of bytes read or -1 if an error occurs
    QFile f;
    char* data=0;
      
   f.setFileName(path);
   if(f.open(QIODevice::ReadOnly))
   {
      *l=f.size();
      data=new char[*l];
      //load all data into char array s
     *l=f.read(data, *l);
      f.close();
   }
   else
   {
    QMessageBox::warning(this, tr("2Pnotes - open file"),
                        tr("Cannot open the requested file\n")+path,
                                    QMessageBox::Ok|QMessageBox::Default);
                                    
      return 0;
   }
   
   return data;
}
   
bool pbase::decodeData(char* d, int l)
{
    //the refered pointer d points to the array with the encrypted data
    //if the returnvalue is true, the array d contains the decoded data
    
    if(!baPbaseKey->isEmpty() && d != 0)
    {
        CBlowFish bf;
        //Blowfish decryption
    bf.initialize((BYTE*)baPbaseKey->data(), (int)strlen(baPbaseKey->data()));
    bf.decode((BYTE*)d, (BYTE*)d, (DWORD)l);
    return true;
    }
    else
        qWarning("Function decodeData(char* d, int l), key is empty or d* is 0\n");
        
    return false;
}

bool pbase::write2file_v01(const QString& path)
//path includes the filename.
{
   QFile f;
   QByteArray baData;
   CBlowFish bf;
   unsigned int le;
   char *e=NULL;
   char v[2];

   //set fileversion
   v[0]=FILEVERSION_MAJOR;
   v[1]=FILEVERSION_MINOR;

   f.setFileName(path);
   if(f.open(QIODevice::WriteOnly))
   {
      int i, l, coe;
      unsigned int j;
      char number[sizeof(int)];
      QString *sbm=new QString();
    QString *spw=new QString();
    QString *srm=new QString();
      
      //build the fileheader
      coe=mem->countOfItems();
      copyByte(number, (char*)&coe, sizeof(int), 0);
      for(j=0; j<sizeof(int); j++)
        baData+=number[j];

      baData+=filelabel;
      baData+=v[0];
      baData+=v[1];
      
      for(i=0; i<coe; i++)
      {
        *sbm=mem->getBookmark(i);
        *spw=mem->getPassword(i);
        *srm=mem->getRemarks(i);
        
        l=sbm->size();
        copyByte(number, (char*)&l, sizeof(int), 0);
        for(j=0; j<sizeof(int); j++)
            baData+=number[j];
        
        l=spw->size();
        copyByte(number, (char*)&l, sizeof(int), 0);
        for(j=0; j<sizeof(int); j++)
            baData+=number[j];

        l=srm->size();
        copyByte(number, (char*)&l, sizeof(int), 0);
        for(j=0; j<sizeof(int); j++)
            baData+=number[j];
                
        baData+=*sbm;   //use the toAscii-function
        baData+=*spw;   //use the toAscii-function
        baData+=*srm;   //use the toAscii-function
        
        sbm->clear();
        spw->clear();
        srm->clear();
      }
      
      l=baData.size();  //summary of length of all data 
      
      //Blowfish encryption
      bf.initialize((BYTE*)baPbaseKey->data(), baPbaseKey->size());
      le = bf.getOutputLength((DWORD)l);
      e = new char[le];
      le = bf.encode((BYTE*)baData.data(), (BYTE*)e,(DWORD)l);

      f.write(e, le);
        f.close();
      delete e;
        delete sbm;
        delete spw;
        delete srm;
   }
   else
   {
    QMessageBox::warning(this, tr("2Pnotes - write file"),
                        tr("Cannot open the requested file for write access\n")+path,
                                                        QMessageBox::Ok|QMessageBox::Default);
                                                        
        return false;
   }

   return true;
}

unsigned int pbase::copyByte(char *dest, char *src, uint cb, uint pos)
//copy cb bytes from src to dest, starting at pos. Returns pos behind the
//last copying char. 
{
   char *d, *s;
   uint i, p;

   d=dest+pos;
   s=src;
   p=pos;

   for(i=0; i<cb; i++)
   {
      *(d++)=*(s++);
      p++;
   }

   return p;
}
