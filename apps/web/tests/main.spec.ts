import { test, expect } from '@playwright/test';
import path from 'path';


test( 'has title', async ({page}) => {
    await page.goto('http://localhost:5173');

    await expect(page).toHaveTitle(/HiddenFrame/);
});

test('should upload an image successfully', async ({ page }) => {

    await page.goto('http://localhost:5173');
  
    const fileInput = page.locator('input[name="file"]');
  
    const filePath = path.resolve('public/HF_logo_light.png');
    
    await fileInput.setInputFiles(filePath);
  
    await page.fill('input[name="message"]', 'Test message');
  
    await page.click('button[type="submit"]');
  
    const uploadedImage = page.locator('img[src*="/static/"]').first(); 
    await expect(uploadedImage).toBeVisible();
  });