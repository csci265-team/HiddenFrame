import { test, expect } from '@playwright/test';

test( 'has title', async ({page}) => {
    await page.goto('http://localhost:5173/login');

    await expect(page).toHaveTitle(/HiddenFrame/);
});

test('has login label', async ({ page }) => {
    await page.goto('http://localhost:5173/login');
    
    await expect(page.locator('h2')).toHaveText(/Login/);
});

test('should register and log in successfully with valid credentials', async ({page}) =>{
    await page.goto('http://localhost:5173/register');

    await page.fill('input[name="username"]', 'correctUsername');
    await page.fill('input[name="password"]', 'correctPassword');

    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173/login');

    await page.fill('input[name="username"]', 'correctUsername');
    await page.fill('input[name="password"]', 'correctPassword');
    
    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173'); // go back to main page if login successfull
});

test('should not log in successfully with invalid username', async ({page}) =>{
    await page.goto('http://localhost:5173/register');

    await page.fill('input[name="username"]', 'correctUsername');
    await page.fill('input[name="password"]', 'correctPassword');

    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173/login');

    await page.fill('input[name="username"]', 'wrongUsername');
    await page.fill('input[name="password"]', 'correctPassword');
    
    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173/login'); // stay on login page if login unsuccessfull
});


test('should not log in successfully with invalid password', async ({page}) =>{
    await page.goto('http://localhost:5173/register');

    await page.fill('input[name="username"]', 'correctUsername');
    await page.fill('input[name="password"]', 'correctPassword');

    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173/login');

    await page.fill('input[name="username"]', 'correctUsername');
    await page.fill('input[name="password"]', 'wrongPassword');
    
    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173/login'); // stay on login page if login unsuccessfull
});

test('should not log in successfully with invalid credentials', async ({page}) =>{
    await page.goto('http://localhost:5173/register');

    await page.fill('input[name="username"]', 'correctUsername');
    await page.fill('input[name="password"]', 'correctPassword');

    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173/login');

    await page.fill('input[name="username"]', 'wrongUsername');
    await page.fill('input[name="password"]', 'wrongPassword');
    
    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173/login'); // stay on login page if login unsuccessfull
});

test('should show error when username or password is missing', async ({ page }) => {
    await page.goto('http://localhost:5173/register');

    await page.fill('input[name="username"]', 'correctUsername');
    await page.fill('input[name="password"]', 'correctPassword');

    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173/login');

    await page.fill('input[name="password"]', 'somePassword');
    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173/login') // stay on login page if login unsuccessfull

    await page.goto('http://localhost:5173/login');

    await page.fill('input[name="username"]', 'someUser');
    await page.fill('input[name="password"]', '');
    await page.click('button[type="submit"]');

    await expect(page).toHaveURL('http://localhost:5173/login') // stay on login page if login unsuccessfull
  });









