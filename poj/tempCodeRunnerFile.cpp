
{
    if (s[l] == '(' && s[r] == ')') return true;
    if (s[l] == '[' && s[r] == ']') return true;
    return false;
}
int main()
{
    while (~scanf("%s", s) && s[0] != 'e')
    {