/*
 * Approximate the number pi using polygons
 *
 * Procedure:
 * Sweep the first quarter of the circumference.
 * Iterate over Y axis and calculate the corresponding X using the Pythagorean theorem.
 * Calculate and accumulate the distance between the current point and the previous point.
 *
 * circumference = quarter * 4
 * pi = circumference / diameter
 *
 * Jesús Ángel González Novez
 * Dec 11, 2018
 */
const NAME = 'pi.js';
const VERSION = 'v1.0'
const DEF_DIAMETER = 100000;

const distance = (x1, y1, x2, y2) => Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
const leg = (l, h) => Math.sqrt(h * h - l * l);

const calculate_pi = diameter => {
    const radius = diameter / 2;
    let quarter = 0;
    let x;
    let y = 1;
    let prev_x = radius;
    let prev_y = 0;

    // First point: (radius, 0)
    // Sweep first quarter

    while (y <= radius) {
        x = leg(y, radius);
        quarter += distance(x, y, prev_x, prev_y);
        prev_x = x;
        prev_y = y++;
    }

    // pi = circumference / diameter
    return quarter * 2 / radius;
}

const help = () => {
    console.log(`PI calculator - ${VERSION}`);
    console.log(`Usage: node ./${NAME} [ diameter ]`);
    console.log(`    diameter    Diameter of the circumference. Default: ${DEF_DIAMETER}`);
    console.log("The larger the diameter, the better the accuracy.");
    process.exit(0)
}


let diameter = DEF_DIAMETER;

if (process.argv.length > 2) {
    if (process.argv[2] === '--help') {
        help();
    }

    diameter = process.argv[2];

    if (diameter <= 0) {
        console.error(`Bad diameter: ${diameter}. Expecting positive integer number.\n`);
        process.exit(1)
    }
}


const pi = calculate_pi(diameter);

console.log(`Pi (calculated) = ${pi.toFixed(16)}`);
console.log(`Pi (predefined) = ${Math.PI.toFixed(16)}`);
console.log(`     difference = ${Math.abs(pi - Math.PI).toFixed(16)}`);
process.exit(0)