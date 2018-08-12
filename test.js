const clippy = require('./index.js')
	// clipboard.paste()
	// clipboard.copy("Xofure")

// console.log('1')
// console.log(clippy.calculateSync(1000000))
// console.log('2')

// function huon () {
// 	return new Promise((resolve, reject) => {
// 	 	clippy.calculateAsync(1000000, (err, res) => {
// 	 		if (err) reject(err)
// 			resolve(res)
// 		})
// 	})
// }
// huon()
// .then((res) => {
// 	console.log(res)
// })
// console.log('3')

console.log(clippy.pasteSync())
clippy.paste((err, res) => console.log('HEO' + res))
console.log(clippy.pasteSync())

console.log('Beforeur')
clippy.copy("Perffeto", (err, res) => {
	console.log('In')
	console.log(res)
})
console.log('Afteureur')