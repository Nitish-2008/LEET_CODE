class Solution {
public:
    string convert(string s, int numRows) {

if (numRows == 1 || numRows >= s.length())
    return s;

    string row [1000];

    int currentRow = 0;
    bool down = true;

    for (int i = 0 ; i <s.length() ; i++ ){
        row[currentRow] += s[i];

        if (currentRow == 0)
            down = true;
        else if (currentRow == numRows - 1)
            down = false;
        
        if (down)
            currentRow++;
        else
            currentRow--;

    }
    string ans = "";

    for (int i = 0 ; i<numRows ; i++){
        ans += row[i];
    }
    return ans;


    }
};