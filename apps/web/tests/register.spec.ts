import { test, expect } from '@playwright/test';

test( 'has title', async ({page}) => {
    await page.goto('http://localhost:5173/register');

    await expect(page).toHaveTitle(/HiddenFrame/);
});

test('has register label', async ({ page }) => {
    await page.goto('http://localhost:5173/register');
    
    await expect(page.locator('h2')).toHaveText(/Register/);
});

