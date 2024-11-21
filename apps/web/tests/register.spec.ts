import { test, expect } from '@playwright/test';

test( 'has title', async ({page}) => {
    await page.goto('http://localhost:5173/register');

    await expect(page).toHaveTitle(/HiddenFrame/);
});

test('has register label', async ({ page }) => {
    await page.goto('http://localhost:5173/register');
    
    await expect(page.locator('h2')).toHaveText(/Register/);
});

test('should not register successfully, if the username already exists', async ({ page }) => {
    await page.goto('http://localhost:5173/register/admin');

    await page.fill('input[name="username"]', 'sameUsername');
    await page.fill('input[name="password"]', 'samePassword');

    await page.click('button[type="submit"]');
    await page.waitForLoadState('networkidle');

    await expect(page).toHaveURL('http://localhost:5173/login'); // go to login page if registration successful

    await page.goto('http://localhost:5173/register/admin');

    await page.fill('input[name="username"]', 'sameUsername');
    await page.fill('input[name="password"]', 'samePassword');

    await page.click('button[type="submit"]');
    await page.waitForLoadState('networkidle');

    await expect(page).toHaveURL('http://localhost:5173/register/admin'); // stay on register page if registration unsuccessfull

});

test('should not register successfully with missing username or password', async ({ page }) => {
    await page.goto('http://localhost:5173/register/admin');

    await page.fill('input[name="username"]', 'usernmae');
    await page.fill('input[name="password"]', '');

    await page.click('button[type="submit"]');
    await page.waitForLoadState('networkidle');

    await expect(page).toHaveURL('http://localhost:5173/register/admin'); // stay on register page if registration unsuccessfull

    await page.goto('http://localhost:5173/register/admin');

    await page.fill('input[name="username"]', '');
    await page.fill('input[name="password"]', 'password');

    await page.click('button[type="submit"]');
    await page.waitForLoadState('networkidle');

    await expect(page).toHaveURL('http://localhost:5173/register/admin'); // stay on register page if registration unsuccessfull

});
