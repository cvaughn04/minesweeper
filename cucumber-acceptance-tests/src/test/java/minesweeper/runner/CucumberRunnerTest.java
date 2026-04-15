package minesweeper.runner;

import org.junit.platform.suite.api.ConfigurationParameter;
import org.junit.platform.suite.api.IncludeEngines;
import org.junit.platform.suite.api.SelectClasspathResource;
import org.junit.platform.suite.api.Suite;

import static io.cucumber.junit.platform.engine.Constants.GLUE_PROPERTY_NAME;
import static io.cucumber.junit.platform.engine.Constants.PLUGIN_PROPERTY_NAME;

/**
 * JUnit 5 suite runner for all Cucumber feature files.
 *
 * - @Suite          → marks this class as a JUnit Platform suite
 * - @IncludeEngines → tells the suite to use the Cucumber engine
 * - @SelectClasspathResource("features") → points to src/test/resources/features/
 * - GLUE_PROPERTY_NAME → package that contains the step definitions
 * - PLUGIN_PROPERTY_NAME → reporting plugins (pretty console + HTML report)
 */
@Suite
@IncludeEngines("cucumber")
@SelectClasspathResource("features")
@ConfigurationParameter(key = GLUE_PROPERTY_NAME,   value = "minesweeper.stepdefinitions")
@ConfigurationParameter(key = PLUGIN_PROPERTY_NAME, value = "pretty, html:target/cucumber-reports/report.html")
public class CucumberRunnerTest {
    // This class is intentionally empty.
    // Cucumber discovers and runs all .feature files via the annotations above.
}
