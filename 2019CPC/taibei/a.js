const fs = require('fs');

const t = fs.readFileSync('out.txt', 'utf8').split('\n').filter(s => s.trim().length > 0).map(s => s.trim().toUpperCase()).map(s => `"${s}"`);

console.log(t.join(','));

// // 读取文件的r g b a 数据
// function getImgData(p){
//     return new Promise((resolve,reject)=>{
//         fs.createReadStream(p)
//             .pipe(new PNG({
//                 filterType: 4
//             }))
//             .on('parsed', function() {
//                 var data= new Buffer.alloc(4*this.width*this.height);
//                 this.data.copy(data);
//                 resolve({
//                     data:data,
//                     width:this.width,
//                     height:this.height
//                 });
//             }
//         );
//     })
// }
 
// // 获取图片后灰度处理
// getImgData('a.png').then((res)=>{
//   let {width,height,data} = res;
//   const ans = [];
//   for(let i = 0; i < height; i++){
//     const arr = [];
//     ans.push(arr);
//     for(let j = 0; j < width; j++){
//       var idx = (width * i + j) << 2;
//       arr.push([data[idx], data[idx + 1], data[idx + 2]]);
//     }
//   }
//   return { width, height, data: ans };
// })
// .then(({ width, height, data }) => {
//   // console.log(width, height);
//   // console.log(data);
//   const ans = [];
//   for (let i = 3, k = 0; k < 64; k++, i += 15) {
//     for (let j = 4, k = 0; k < 64; k++, j += 15) {
//       // console.log(data[i + 8][j + 8]);
//       if (data[i + 8][j + 8][0] === 237) {
//         ans.push(1);
//       } else {
//         ans.push(0);
//       }
//     }
//   }
//   console.log(ans.join(','));
// })
// .catch((e)=>{
//     console.log("错误:",e);
// });