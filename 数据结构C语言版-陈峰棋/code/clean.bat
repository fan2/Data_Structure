@ echo --------------------------------------------
@ echo 清理Debug目录和Release目录。
@ echo --------------------------------------------
@ echo
pause
echo 清理开始
FOR /R . %%d IN (.) DO rd /s /q "%%d\Debug" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\Release" 2>nul
del /q/s *.user
echo 清理结束
echo. & pause