state =1
while((ch=getc(fp))!='#' )
{
  state_before=state;
  state=state_change(state,ch);
   if(state)
       token[i++]=ch;
    else
    {
       reset(fp,token,state);
       code=state_to_code(state_before,token);
       parse(code);
     }
}
