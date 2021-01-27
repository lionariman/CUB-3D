make clean
cp -R ~/cursus/cub3d/* ~/cursus/cub
cd ../cub
git add .
git commit -m "no memory leaks"
git push origin main
cd ../cub3d
