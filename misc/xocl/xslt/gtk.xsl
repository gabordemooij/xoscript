<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="xml" indent="yes"/>
	<!-- Root -->
	<xsl:template match="/">
		<interface>
			<requires lib="gtk" version="4.0"/>
			<object class="GtkWindow" id="window">
				<property name="title">
					<xsl:value-of select="html/head/title"/>
				</property>
				<property name="default-width">
					<xsl:value-of select="html/body/@width"/>
				</property>
				  <property name="default-height">
					<xsl:value-of select="html/body/@height"/>
				</property>
				<child>
					<object class="GtkBox" id="main_box">
						<property name="orientation">vertical</property>
						<property name="spacing">8</property>
						<xsl:apply-templates select="html/body/*"/>
					</object>
				</child>
			</object>
		</interface>
	</xsl:template>
	<xsl:template name="gtk-style">
		<xsl:if test="@class">
			<style>
				<class name="{@class}"/>
			</style>
		</xsl:if>
	</xsl:template>
	<!-- FORM -->
	<xsl:template match="form">
		<xsl:call-template name="gtk-style"/>
		<child>
			<object class="GtkBox">
				<xsl:if test="@id">
					<xsl:attribute name="id">
						<xsl:value-of select="@id"/>
					</xsl:attribute>
				</xsl:if>
				<property name="orientation">vertical</property>
				<property name="spacing">6</property>
				<xsl:apply-templates/>
			</object>
		</child>
	</xsl:template>
	<!-- DIV -->
	<xsl:template match="div">
		<child>
			<object class="GtkBox">
				<property name="orientation">horizontal</property>
				<property name="spacing">4</property>
				<xsl:apply-templates/>
			</object>
		</child>
	</xsl:template>
	<!-- LABEL -->
	<xsl:template match="label">
		<child>
			<object class="GtkLabel">
				<property name="label">
					<xsl:value-of select="@text"/>
				</property>
				<property name="xalign">0</property>
			</object>
		</child>
	</xsl:template>
	<!-- TEXT INPUT -->
	<xsl:template match="input[@type='text']">
		<xsl:call-template name="gtk-style"/>
		<child>
			<object class="GtkEntry">
				<xsl:attribute name="id">
					<xsl:value-of select="@id"/>
				</xsl:attribute>
			</object>
		</child>
	</xsl:template>
	<!-- PASSWORD -->
	<xsl:template match="input[@type='password']">
		<xsl:call-template name="gtk-style"/>
		<child>
			<object class="GtkEntry">
				<xsl:attribute name="id">
					<xsl:value-of select="@id"/>
				</xsl:attribute>
				<property name="visibility">False</property>
			</object>
		</child>
	</xsl:template>
	<!-- CHECKBOX -->
	<xsl:template match="input[@type='checkbox']">
		<xsl:call-template name="gtk-style"/>
		<child>
			<object class="GtkCheckButton">
				<xsl:attribute name="id">
					<xsl:value-of select="@id"/>
				</xsl:attribute>
				<property name="label">
					<xsl:value-of select="@text"/>
				</property>
				<property name="active">
					<xsl:choose>
						<xsl:when test="@checked">true</xsl:when>
						<xsl:otherwise>false</xsl:otherwise>
					</xsl:choose>
				</property>
			</object>
		</child>
	</xsl:template>
	<!-- RADIO -->
	<xsl:template match="input[@type='radio']">
		<xsl:call-template name="gtk-style"/>
		<child>
			<object class="GtkCheckButton">
				<xsl:attribute name="id">
					<xsl:value-of select="@id"/>
				</xsl:attribute>
				<property name="label">
					<xsl:value-of select="@text"/>
				</property>
				<xsl:if test="preceding::input[@type='radio' and @name=current()/@name]">
					<property name="group">
						<xsl:value-of
							select="preceding::input[@type='radio' and @name=current()/@name][1]/@id"/>
					</property>
				</xsl:if>
			</object>
		</child>
	</xsl:template>
	<!-- BUTTON -->
	<xsl:template match="button">
		<xsl:call-template name="gtk-style"/>
		<child>
			<object class="GtkButton">
				<xsl:attribute name="id">
					<xsl:value-of select="@id"/>
				</xsl:attribute>
				<property name="label">
					<xsl:value-of select="@text"/>
				</property>
				<property name="name">
					<xsl:value-of select="@name"/>
				</property>
				<xsl:if test="@width">
				<property name="halign">start</property>
				<property name="width-request">100</property>
				</xsl:if>
			</object>
		</child>
	</xsl:template>
	<!-- IMAGE -->
	<xsl:template match="img">
		<xsl:call-template name="gtk-style"/>
		<child>
			<object class="GtkImage">
				<property name="file">
					<xsl:value-of select="@src"/>
				</property>
			</object>
		</child>
	</xsl:template>
	<!-- TABLE -->
	<xsl:template match="table">
		<xsl:call-template name="gtk-style"/>
		<child>
			<object class="GtkGrid">
				<xsl:if test="@id">
					<xsl:attribute name="id">
						<xsl:value-of select="@id"/>
					</xsl:attribute>
				</xsl:if>
				<property name="row-spacing">4</property>
				<property name="column-spacing">8</property>
				<xsl:apply-templates select="tr"/>
			</object>
		</child>
	</xsl:template>
	<!-- TABLE ROW -->
	<xsl:template match="tr">
		<xsl:param name="row"
			select="count(preceding-sibling::tr)"/>
		<xsl:apply-templates select="th | td">
			<xsl:with-param name="row"
				select="$row"/>
		</xsl:apply-templates>
	</xsl:template>
	<!-- TABLE HEADER -->
	<xsl:template match="th">
		<xsl:param name="row"/>
		<xsl:variable name="column"
			select="count(preceding-sibling::th | preceding-sibling::td)"/>
		<child>
			<object class="GtkLabel">
				<property name="label">
					<xsl:value-of select="."/>
				</property>
				<property name="xalign">0</property>
				<property name="css-classes">heading</property>
				<layout>
					<property name="column">
						<xsl:value-of select="$column"/>
					</property>
					<property name="row">
						<xsl:value-of select="$row"/>
					</property>
				</layout>
			</object>
		</child>
	</xsl:template>
	<!-- TABLE CELL -->
	<xsl:template match="td">
		<xsl:param name="row"/>
		<xsl:variable name="column"
			select="count(preceding-sibling::th | preceding-sibling::td)"/>
		<child>
			<object class="GtkBox">
				<property name="orientation">horizontal</property>
				<property name="spacing">4</property>
				<xsl:apply-templates/>
				<layout>
					<property name="column">
						<xsl:value-of select="$column"/>
					</property>
					<property name="row">
						<xsl:value-of select="$row"/>
					</property>
				</layout>
			</object>
		</child>
	</xsl:template>
	<!-- LABEL -->
	<xsl:template match="text()[normalize-space()]">
	<child>
		<object class="GtkLabel">
		<property name="label">
				<xsl:value-of select="normalize-space(.)"/>
			</property>
			<property name="xalign">0</property>
		</object>
	</child>
	</xsl:template>
	<!-- DEFAULT RECURSIVE PASS -->
	<xsl:template match="*">
		<xsl:apply-templates/>
	</xsl:template>
</xsl:stylesheet>
