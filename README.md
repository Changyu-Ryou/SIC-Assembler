# SIC-Assembler
> [Prog] 2019-2 System Software Term Project - C 언어와 리눅스를 이용한 SIC 어셈블러 설계 및 개발<br/>
C 언어와 리눅스를 이용한 SIC 어셈블러 설계 및 개발  

<br/><br/>
  
## ✨ The Simplified Instructional Computer Architecture 설계이슈
> 넘버링된 것은 설계이슈이고, 그 아래에는 팀에서 결정한 설계 방식이 적혀있습니다.
1. The Simplified Instructional Computer의 CPU Micro-Instruction Set을 결정한다.  
   - Register-related instructions, Integer arithmetic operations, Conditional jump instructions, Subroutine Linkage instructions. (LDA, LDX, STA, STX, ADD, SUB, MUL, DIV, JLT, JEQ, JGT, JSUB, RSUB, etc.)
   <br/>
2. The Simplified Instructional Computer의 Main Memory Capacity를 결정한다.  
   - 32,768()byte
   <br/>
3. The Simplified Instructional Computer의 Addressing Mode(s)를 결정한다.  
   - Direct Mode, Indexed Mode
   <br/>
4. The Simplified Instructional Computer의 CPU Instruction Format(s)를 결정한다.
   - 3-bytes Format
   <br/>
5. The Simplified Instructional Computer의 Register(s)를 결정한다.
   - 직접적으로 Register(s)를 사용하지는 않는다.
   <br/>
6. The Simplified Instructional Computer의 데이터 포맷(Data Forma ts)을 결정한다.
   - Integer Data Format, Character Data Format

  <br/><br/>
## 📖 The Simplified Instructional Computer Assembler 설계이슈  
> 넘버링된 것은 설계이슈이고, 그 아래에는 팀에서 결정한 설계 방식이 적혀있습니다.
1. 어셈블러의 아키텍처를 결정한다. 
   - Two-pass
   <br/>
2. Micro-Instruction Set Table을 위한 데이터구조를 결정한다.
   - Array (구조체 배열 사용)
   <br/>
3. Micro-Instruction Set Table의 검색 알고리즘을 결정한다. 
   - 순차 알고리즘, 키워드를 사용하여 직접 검색
   <br/>
4. 어셈블리언어상의 Addressing Mode 표기방법을 결정한다. (설계이슈 3의 결정에 따른 지원)
   - x가 0일 경우 Direct Mode, x가 1일 경우 Indexed Mode
   <br/>
5. 어셈블리언어상의 Directive Instructions을 결정한다.
   - START, END., RESW, REWB, BYTE, WORD 등 프로그램 편리성 제공을 위한 명령어
   <br/>
6. 어셈블리 프로그램에 대한 최종 산출물인 프로그램 Object Codes의 구조를 결정한다.
   - H, T, E 레코드 형식 구조


  <br/><br/>
## 👨‍💻 어셈블러의 설계 및 구현 (어셈블러의 IPO 모델)
<img src="https://user-images.githubusercontent.com/56837413/74592260-d5ab1e80-5062-11ea-961a-81b817e0c4a8.PNG" width="80%"></img>
  <br/><br/>
  
## 📗 Input File - assemProg.txt
  
<pre><code>
5 COPY START 1000 COPY FILE
10 FIRST STL RETADR SAVE RETURN ADDRESS
15 CLOOP LDA LENGTH TEST FOR EOF
20 COMP ZERO
25 JEQ ENDFIL EXIT IF EOF FOUND
30 J CLOOP LOOP
35 ENDFIL LDA EOF INSERT END OF FILE
40 STA BUFFER
45 LDA THREE SET LENGTH = 3
50 STA LENGTH
55 LDL RETADR GET RETURN ADDRESS
60 EOF BYTE C’EOF’
65 THREE WORD 3
70 ZERO WORD 0
75 RETADR RESW 1
80 LENGTH RESW 1 LENGTH OF RECORD
85 BUFFER RESB 4096 4096-BYTE BUFFER
90 END FIRST
</code></pre>
기존 Term Project 계획서에서 주어졌던 Input 값을 사용하였다.  
SIC Assembler에서 사용되는 instruction을 포함하고 있다.
  <br/><br/>

## 📗 Output File - Symbol Table File  
<img src="https://user-images.githubusercontent.com/56837413/74592567-e01ae780-5065-11ea-804c-cbbad7c26724.jpg" width="20%"></img>  
Input File을 넣은 뒤, Symbol Table의 내용들을 ‘assemProg.t‘ 파일에 저장한다. (앞의 assemProg 부분은 strtok을 이용하여 Input File명에서 받아온 값이다.)  
Loc 부분에 오류가 생길 경우 틀린 위치를 바로 확인할 수 있으므로 이 파일을 이용할 경우 코드를 손쉽게 수정할 수 있다.
<br/><br/>
## 📗 Output File - Object Program
<img src="https://user-images.githubusercontent.com/56837413/74592554-d1cccb80-5065-11ea-9435-dc254f252e7c.jpg" width="80%"></img>  
최종 결과물인 Object Program을 ‘objectProg.txt’ 명으로 저장한다. 설계이슈에서 작성하였던 것처럼 Header, Text, End 레코드들로 구성된다.  
Header Record 부분은 Input File의 명이 ‘COPY’라는 것을 확인할 수 있고, 시작주소와 프로그램의 총 길이가 명시되어 있다.  
첫 번째 Text Record 부분은 시작주소를 알 수 있고, 그다음 열에는 해당 행의 길이가 명시되어 있다. 다음 열부터 Object code가 삽입된다.  
Text Record 부분이 한 줄 더 늘어나 있는 것을 볼 수 있다. 이것은 Object Program을 만드는 과정에서 한 행의 Object Code의 길이가 30-byte를 넘어서면 개행을 하므로 Text Record가 한 줄 더 작성된다.  
<br/>
마지막으로 End Record 부분은 코드의 마지막을 알리는 행이다. 첫 번째 줄로 이동할 수 있으므로 시작주소의 값을 명시해준다.  
<br/><br/>

## 📝 실행 결과  
> ### 과정 1  
<img src="https://user-images.githubusercontent.com/56837413/74592589-26704680-5066-11ea-9cf4-c618f0d8ccb9.PNG" width="70%"></img>  
<br/>

> ### 과정 2  
<img src="https://user-images.githubusercontent.com/56837413/74592591-283a0a00-5066-11ea-96fa-3f9f0cdc9a0f.PNG" width="70%"></img>  
<br/>

> ### 과정 3  
<img src="https://user-images.githubusercontent.com/56837413/74592592-296b3700-5066-11ea-85b9-67aafdb39bdc.PNG" width="70%"></img>  
<br/>

> ### 최종 화면 
<img src="https://user-images.githubusercontent.com/56837413/74592594-2bcd9100-5066-11ea-9f53-6a0b32e74595.PNG" width="70%"></img>  
<br/>

> ### 최종 제출 파일
<img src="https://user-images.githubusercontent.com/56837413/74592596-2e2feb00-5066-11ea-8370-0338874acfe2.PNG" width="40%"></img>  
  <br/> <br/>
  <br/> <br/>
  <br/> <br/>
  
  코드 설명에 대한 더 자세한 내용은 [SS_Term Project_Group E.hwp](https://github.com/Changyu-Ryou/SIC-Assembler/blob/master/report/SS_Term%20Project_Group%20E.hwp)에서 확인하실 수 있습니다.  
  
  감사합니다.
