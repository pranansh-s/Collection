const inputFile = document.getElementById("input");
const videoPreview = document.getElementById("video-input");
const scalePercent = document.getElementById("scale-percent");
const convertBtn = document.getElementById("convert");
const downloadBtn = document.getElementById("download");
const canvas = document.getElementById("canvas");

const ASCII_MAP = [' ', '.', "'", '`', '^', '"', ',', ':', ';', 'I', 'l', '!', 
                  'i', '>', '<', '~', '+', '_', '-', '?', ']', '[', '}', '{', 
                  '1', ')', '(', '|', '\\', '/', 't', 'f', 'j', 'r', 'x', 'n', 
                  'u', 'v', 'c', 'z', 'X', 'Y', 'U', 'J', 'C', 'L', 'Q', '0', 
                  'O', 'Z', 'm', 'w', 'q', 'p', 'd', 'b', 'k', 'h', 'a', 'o', 
                  '*', '#', 'M', 'W', '&', '8', '%', 'B', '@', '$'];

let asciiFrames = [];
let videoStream;
let mediaRecorder;
let recordedChunks = [];

const handleVideoPreview = () => {
    const file = inputFile.files[0];
    if (file) {
        videoPreview.src = URL.createObjectURL(file);
        videoPreview.style.display = "block";
        videoPreview.load();
        videoPreview.muted = true;
    }
}

const convertToASCII = (imageData) => {
    const pixels = imageData.data;
    let asciiImage = '';
    
    const scale = Math.max(0.1, Math.min(1, parseInt(scalePercent.innerText) / 100));
    const step = Math.max(1, Math.floor(5 * (1 - scale)));

    for (let py = 0; py < canvas.height; py += step * 2) {
        for (let px = 0; px < canvas.width; px += step) {
            const pixelIndex = (py * canvas.width + px) * 4;
            const r = pixels[pixelIndex];
            const g = pixels[pixelIndex + 1];
            const b = pixels[pixelIndex + 2];
            const brightness = (r + g + b) / 3;
            
            const charIndex = Math.floor((brightness / 255) * (ASCII_MAP.length - 1));
            asciiImage += ASCII_MAP[charIndex];
        }
        asciiImage += '\n';
    }
    return asciiImage;
};

const renderASCIIToCanvas = (asciiFrame) => {
    const ctx = canvas.getContext('2d');
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = 'black';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    
    const fontSize = Math.floor(canvas.width / asciiFrame.split('\n')[0].length * 2);
    ctx.font = `${fontSize}px monospace`;
    ctx.fillStyle = 'white';
    
    const lines = asciiFrame.split('\n');
    const lineHeight = fontSize * 1.2;
    const startY = fontSize;
    
    for (let i = 0; i < lines.length; i++) {
        ctx.fillText(lines[i], 0, startY + i * lineHeight);
    }
}

const handleAsyncFrames = async () => {
    convertBtn.disabled = true;
    downloadBtn.disabled = true;
    asciiFrames = [];
    recordedChunks = [];
    
    const ctx = canvas.getContext("2d");
    const frameRate = 15;
    const frameInterval = 1000 / frameRate;
    let currentTime = 0;
    
    videoStream = canvas.captureStream(frameRate);
    mediaRecorder = new MediaRecorder(videoStream, {
        mimeType: 'video/webm'
    });
    
    mediaRecorder.ondataavailable = (e) => {
        if (e.data.size > 0) recordedChunks.push(e.data);
    };
    
    mediaRecorder.start();
    
    while (currentTime < videoPreview.duration) {
        const startTime = performance.now();
        
        videoPreview.currentTime = currentTime;
        await new Promise(resolve => {
            videoPreview.onseeked = resolve;
        });

        ctx.drawImage(videoPreview, 0, 0, canvas.width, canvas.height);
        
        const frameData = ctx.getImageData(0, 0, canvas.width, canvas.height);
        const asciiFrame = convertToASCII(frameData);
        asciiFrames.push(asciiFrame);
        renderASCIIToCanvas(asciiFrame);

        const processingTime = performance.now() - startTime;
        const remainingTime = Math.max(0, frameInterval - processingTime);
        
        if (remainingTime > 0) {
            await new Promise(resolve => setTimeout(resolve, remainingTime));
        }
        
        currentTime += 1 / frameRate;
    }
    
    mediaRecorder.stop();
    convertBtn.disabled = false;
    downloadBtn.disabled = false;
}

const handleScaleChange = (val) => {
    scalePercent.innerText = `${val}%`;
}

convertBtn.addEventListener('click', handleAsyncFrames);
downloadBtn.addEventListener('click', () => {
    if (recordedChunks.length === 0) {
        console.warn("No video recorded yet");
        return;
    }

    const blob = new Blob(recordedChunks, { type: 'video/webm' });
    const url = URL.createObjectURL(blob);
    
    const a = document.createElement('a');
    a.href = url;
    a.download = 'ascii-video.webm';
    document.body.appendChild(a);
    a.click();

    setTimeout(() => {
        document.body.removeChild(a);
        URL.revokeObjectURL(url);
    }, 100);
});

inputFile.addEventListener('change', handleVideoPreview);