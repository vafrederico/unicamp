/*
 * The BodgeIt Store and its related class files.
 *
 * The BodgeIt Store is a vulnerable web application suitable for pen testing
 *
 * Copyright 2011 psiinon@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.thebodgeitstore.selenium.tests;

import com.thoughtworks.selenium.SeleneseTestCase;
import org.apache.commons.lang.RandomStringUtils;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.io.File;

/*
 * Note that this is an example of how to use ZAP with Selenium tests,
 * not a good example of how to write good Selenium tests!
 */
public class LoginUserTest extends SeleneseTestCase {

	private WebDriver driver;
    private static String correctUsername = "usuario@dominio.com";
    private static String wrongUsername = "usuarioerrado@dominio.com";
    private static String correctPassword = "senha";
    private static String wrongPassword = "senhaerrada";
	public void setUp() throws Exception {
		String target = System.getProperty("zap.targetApp");
		File classpathRoot = new File(System.getProperty("user.dir"));
		File chromedriver = new File("/home/ec2012/ra139223/AutomationProjectCS/driver/chromedriver");
		System.setProperty("webdriver.chrome.driver", chromedriver.getAbsolutePath());
		this.setDriver(new ChromeDriver());
	}
	
	private void sleep() {
		try {
			Thread.sleep(300);
		} catch (InterruptedException e) {
			// Ignore
		}
		
	}

	private void fillInput(WebElement element, String value){
		element.clear();
        sleep();
        element.sendKeys(value);
	}

	private void login(String username, String password){
        driver.navigate().to("http://143.106.73.20:8080/bodgeit/login.jsp");
		fillInput(driver.findElement(By.id("username")), username);
        fillInput(driver.findElement(By.id("password")), password);
        driver.findElement(By.id("submit")).click();
	}

	public void testLogin() {
        login(wrongUsername, correctPassword);
        assertTrue(driver.findElement(By.tagName("body")).getText().contains("You supplied an invalid name or password."));
        login(correctUsername, wrongPassword);
        assertTrue(driver.findElement(By.tagName("body")).getText().contains("You supplied an invalid name or password."));
        login(correctUsername, correctPassword);
        assertTrue(driver.findElement(By.tagName("body")).getText().contains("You have logged in successfully: usuario@dominio.com"));
    }

	public void tearDown() throws Exception {
		driver.close();
	}

	protected WebDriver getDriver() {
		return driver;
	}

	protected void setDriver(WebDriver driver) {
		this.driver = driver;
	}

	public static void main(String[] args) throws Exception {
		LoginUserTest test = new LoginUserTest();
		test.setUp();
		test.testLogin();
		test.tearDown();
		
	}

}
