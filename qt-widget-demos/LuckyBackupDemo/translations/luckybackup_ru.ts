<?xml version="1.0" ?><!DOCTYPE TS><TS language="ru" sourcelanguage="en" version="2.0">
<context>
    <name>CalcDiffThread</name>
    <message>
        <location filename="../src/calcDiffThread.cpp" line="+61"/>
        <source>Scanning destination</source>
        <translation>Сканирование каталога Назначение</translation>
    </message>
    <message>
        <location line="+0"/>
        <location line="+74"/>
        <location line="+51"/>
        <location line="+3"/>
        <source>Please wait</source>
        <translation>Пожалуйста, подождите</translation>
    </message>
    <message>
        <location line="-54"/>
        <source>Scanning snapshot</source>
        <translation>Сканирование каталога резервной копии</translation>
    </message>
    <message>
        <location line="+51"/>
        <source>Scanning source</source>
        <translation>Сканирование каталога источника</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Calculating differences</source>
        <translation>Определение различий</translation>
    </message>
    <message>
        <location line="+114"/>
        <source>Sync dir A &amp; B differences</source>
        <translation>Различия между синхронизируемыми каталогами A и B</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Snapshot and source differences</source>
        <translation>Различия между резервной копией и каталогом Источника</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Sync dir B data that also exists at sync dir A and is different</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+3"/>
        <source>Snapshot data that also exists at the source and is different</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>The snapshot data will replace the source data during RESTORE</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+4"/>
        <location line="+15"/>
        <location line="+16"/>
        <source>Data amount is huge. Displaying only first entries</source>
        <translation>Большой объём данных. Показаны только первые записи</translation>
    </message>
    <message>
        <location line="-24"/>
        <source>Sync dir B data that do NOT exist at sync dir A</source>
        <translation>Файлы в каталоге B, которых не существует в каталоге A</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Snapshot data that do NOT exist at the source</source>
        <translation>Файлы резервной копии, которых НЕТ в Источнике</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>These will be transfered over at the source during RESTORE</source>
        <translation>Они будут перемещены на Источник в задаче ВОССТАНОВЛЕНИЕ</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>Sync dir A data that do NOT exist at sync dir B</source>
        <translation>Файлы в каталоге A, которых не существует в каталоге B</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Source data that do NOT exist at the snapshot</source>
        <translation>Файлы в источнике, которых НЕТ в резервной копии</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>These will be deleted during RESTORE only if you enable the option:</source>
        <translation>Они могут быть удалены в задаче ВОССТАНОВЛЕНИЕ, только если вы указали опцию:</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>delete existing source data that do not exist at the backup</source>
        <translation>Удалять отсутствующие файлы</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/global.cpp" line="+1145"/>
        <source>The task list is empty</source>
        <translation>Список задач пустой</translation>
    </message>
    <message>
        <location line="+1"/>
        <location line="+51"/>
        <source>nothing to start</source>
        <translation>нечего выполнять</translation>
    </message>
    <message>
        <location line="-12"/>
        <source>You have included both of the following connected tasks:</source>
        <translation>Вы выбрали две связанные задачи:</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>this is not allowed for obvious reasons</source>
        <translation>это не допускается по понятным причинам</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Please &lt;b&gt;uncheck appropriate include boxes&lt;/b&gt; before proceeding</source>
        <translation>Пожалуйста, &lt;b&gt;исключите ненужную задачу&lt;/b&gt; перед продолжением</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>You have not included any tasks</source>
        <translation>Не выбрано ни одной задачи</translation>
    </message>
    <message>
        <location line="+51"/>
        <source>The following included tasks &lt;b&gt;share the same destination directory&lt;/b&gt; (all together or at groups) and at least one of them will backup the contents of a directory</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+2"/>
        <source>this will lead to one task canceling the other</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>Please uncheck appropriate include boxes or change all task types to other than &apos;&lt;b&gt;Backup dir contents&lt;/b&gt;&apos;  or use &apos;Backup dir contents&apos; together with the &apos;&lt;b&gt;Only include&lt;/b&gt;&apos; option, before proceeding</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+674"/>
        <source>pre-task execution of command</source>
        <comment>Full phrase: pre-task execution of command: &lt;COMMAND&gt; starting</comment>
        <translation>Выполнение команд до выполнения задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>starting</source>
        <comment>Full phrase: pre-task execution of command: &lt;COMMAND&gt; starting</comment>
        <translation>начало</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Command re-run due to failure</source>
        <comment>This means that a specific command is run for once more because it failed the first time</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+5"/>
        <source>post-task execution of command</source>
        <comment>Full phrase: post-task execution of command: &lt;COMMAND&gt; starting</comment>
        <translation>Выполнение команд после выполнения задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>starting</source>
        <comment>Full phrase: post-task execution of command: &lt;COMMAND&gt; starting</comment>
        <translation>начало</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>execution of task</source>
        <comment>Full phrase: execution of task: &lt;TASKNAME&gt; starting</comment>
        <translation>Выполнение задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>starting</source>
        <comment>Full phrase: execution of task: &lt;TASKNAME&gt; starting</comment>
        <translation>начало</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Source</source>
        <comment>Full phrase: source: &lt;SOURCE_NAME</comment>
        <translation>Источник</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Destination</source>
        <comment>Full phrase: Destination: &lt;DEST_NAME</comment>
        <translation>Назначение</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>execution of 1st part of task</source>
        <comment>Full phrase: execution of 1st part of task: &lt;TASKNAME&gt; starting</comment>
        <translation>Выполнение первой части задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>starting</source>
        <comment>Full phrase: execution of 1st part of task: &lt;TASKNAME&gt; starting</comment>
        <translation>начало</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Syncing</source>
        <comment>Full phrase: Syncing &lt;DIR-A&gt; to &lt;DIR-B&gt;</comment>
        <translation>Синхронизация</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>to</source>
        <comment>Full phrase: Syncing &lt;DIR-A&gt; to &lt;DIR-B&gt;</comment>
        <translation>и</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>execution of 2nd part of task</source>
        <comment>Full phrase: execution of 2nd part of task: &lt;TASKNAME&gt; starting</comment>
        <translation>Выполнение второй части задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>starting</source>
        <comment>Full phrase: execution of 2nd part of task: &lt;TASKNAME&gt; starting</comment>
        <translation>начало</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Syncing</source>
        <comment>Full phrase: Syncing &lt;DIR-B&gt; to &lt;DIR-A&gt;</comment>
        <translation>Синхронизация</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>to</source>
        <comment>Full phrase: Syncing &lt;DIR-B&gt; to &lt;DIR-A&gt;</comment>
        <translation>и</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>pre-task execution of command</source>
        <comment>Full phrase: pre-task execution of COMMAND: &lt;COMMANDNAME&gt; finished</comment>
        <translation>Выполнение команд до выполнения задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>finished</source>
        <comment>Full phrase: pre-task execution of COMMAND: &lt;COMMANDNAME&gt; finished</comment>
        <translation>конец</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>post-task execution of command</source>
        <comment>Full phrase: post-task execution of COMMAND: &lt;COMMANDNAME&gt; finished</comment>
        <translation>Выполнение команд после выполнения задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>finished</source>
        <comment>Full phrase: post-task execution of COMMAND: &lt;COMMANDNAME&gt; finished</comment>
        <translation>конец</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>execution of 1st part of task</source>
        <comment>Full phrase: execution of 1st part of task: &lt;TASKNAME&gt; finished</comment>
        <translation>Выполнение первой части задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>finished</source>
        <comment>Full phrase: execution of 1st part of task: &lt;TASKNAME&gt; finished</comment>
        <translation>конец</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>execution of task</source>
        <comment>Full phrase: execution of task: &lt;TASKNAME&gt; finished</comment>
        <translation>Выполнение задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>finished</source>
        <comment>Full phrase: execution of task: &lt;TASKNAME&gt; finished</comment>
        <translation>конец</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>execution of task</source>
        <comment>Full phrase: execution of task: &lt;TASKNAME&gt; finished because of pre/post task command execution error</comment>
        <translation>Выполнение задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>finished because of pre/post task command execution error</source>
        <comment>Full phrase: execution of task: &lt;TASKNAME&gt; finished because of pre/post task command execution error</comment>
        <translation>остановлено, потому что команды, выполняющиеся до/после задачи, выполнились с ошибкой</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>The process reported an error</source>
        <translation>Процесс сообщает об ошибке</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>Backing-up profile, logfiles and snapshot data</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+111"/>
        <source>Could not open the logfile</source>
        <translation>Невозможно открыть лог-файл</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>The logfile does not exist</source>
        <translation>Лог-файл не существует</translation>
    </message>
    <message>
        <location line="+78"/>
        <source>The specified command is probably not installed</source>
        <translation>Указанная команда возможно не установлена</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>The logfile could not be created</source>
        <translation>Невозможно создать лог-файл</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>command:   </source>
        <translation>команда:   </translation>
    </message>
    <message>
        <location line="+3"/>
        <source>exit code: </source>
        <translation>код завершения: </translation>
    </message>
    <message>
        <location line="+1"/>
        <source>output:    </source>
        <translation>вывод:    </translation>
    </message>
    <message>
        <location line="+40"/>
        <source>Last execution time</source>
        <translation>Время последнего выполнения</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>not available</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+11"/>
        <source>no errors</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+5"/>
        <source>errors found</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+10"/>
        <location line="+61"/>
        <location line="+99"/>
        <source>status</source>
        <translation>Статус</translation>
    </message>
    <message>
        <location line="-160"/>
        <source>OK</source>
        <translation>OK</translation>
    </message>
    <message>
        <location line="+3"/>
        <location line="+19"/>
        <source>Sync directory</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="-14"/>
        <location line="+108"/>
        <source>Source directory</source>
        <translation>Источник</translation>
    </message>
    <message>
        <location line="-99"/>
        <location line="+19"/>
        <source>Using remote, check is skipped</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="-9"/>
        <location line="+104"/>
        <location line="+59"/>
        <source>Destination directory</source>
        <translation>Назначение</translation>
    </message>
    <message>
        <location line="-137"/>
        <source>free</source>
        <comment>as in free disk space</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+8"/>
        <source>WARNING</source>
        <translation>ПРЕДУПРЕЖДЕНИЕ</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>I do not have the permission to read/enter sync directory A</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+5"/>
        <source>I do not have the permission to read/enter the source directory</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+11"/>
        <source>I do not have the permission to read/enter sync directory B</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+5"/>
        <source>I do not have the permission to read/enter the destination directory</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+9"/>
        <location line="+67"/>
        <source>Directory</source>
        <translation>Каталог</translation>
    </message>
    <message>
        <location line="-65"/>
        <location line="+67"/>
        <source>and/or</source>
        <translation>и/или</translation>
    </message>
    <message>
        <location line="-64"/>
        <source>does not exist</source>
        <translation>не существует</translation>
    </message>
    <message>
        <location line="+2"/>
        <location line="+30"/>
        <source>is not mounted</source>
        <translation>не примонтирован</translation>
    </message>
    <message>
        <location line="-15"/>
        <location line="+74"/>
        <source>is empty or does not exist</source>
        <translation>пустой или не существует</translation>
    </message>
    <message>
        <location line="-45"/>
        <source>I will &lt;font color=red&gt;&lt;b&gt;NOT SKIP&lt;/b&gt;&lt;/font&gt; this task because you have enabled the &quot;by-pass WARNING&quot; option</source>
        <translation>Эта задача &lt;font color=red&gt;&lt;b&gt;НЕ ПРОПУСКАЕТСЯ&lt;/b&gt;&lt;/font&gt; потому что выбрана опция &quot;отключить ПРЕДУПРЕЖДЕНИЯ&quot;</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>This task will be &lt;font color=red&gt;&lt;b&gt;skipped&lt;/b&gt;&lt;/font&gt;</source>
        <translation>Эта задача &lt;font color=red&gt;&lt;b&gt;пропускается&lt;/b&gt;&lt;/font&gt;</translation>
    </message>
    <message>
        <location line="+8"/>
        <source>CRITICAL</source>
        <translation>КРИТИЧНЫЙ</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>is empty</source>
        <translation>пустой</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>I will &lt;font color=orange&gt;&lt;b&gt;not skip&lt;/b&gt;&lt;/font&gt; this task. Synchronizing is going to be performed anyway</source>
        <translation>Эта задача &lt;font color=orange&gt;&lt;b&gt;НЕ ПРОПУСКАЕТСЯ&lt;/b&gt;&lt;/font&gt;. Синхронизация будет выполнена в любом случае</translation>
    </message>
    <message>
        <location line="+25"/>
        <source>This task will &lt;font color=orange&gt;&lt;b&gt;not be skipped</source>
        <translation>Эта задача &lt;font color=orange&gt;&lt;b&gt; не пропускается</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>The Destination Directory will be created if it doesn&apos;t exist and filled with new backup data</source>
        <translation>Если каталог Назначение не существует, он будет создан и заполнен новыми данными резервной копии</translation>
    </message>
    <message>
        <location line="+8"/>
        <source>Task description</source>
        <translation>Описание задачи</translation>
    </message>
</context>
<context>
    <name>aboutDialog</name>
    <message>
        <location filename="../src/about.cpp" line="+65"/>
        <source>using Qt4</source>
        <translation>использует Qt4</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Backup &amp; Sync Application</source>
        <translation>Программа для резервного копирования и синхронизации</translation>
    </message>
    <message>
        <location line="+3"/>
        <location line="+22"/>
        <source>Loukas Avgeriou</source>
        <translation>Loukas Avgeriou</translation>
    </message>
    <message>
        <location line="-11"/>
        <source>It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.</source>
        <translation>Данное программное обеспечение распространяется в надежде, что оно будет полезным, но БЕЗ ВСЯКОЙ ГАРАНТИИ, в том числе без связанной гарантии ТОВАРНОЙ ПРИГОДНОСТИ или ПРИГОДНОСТИ ДЛЯ КОНКРЕТНОГО ПРИМЕНЕНИЯ.</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>See the &apos;License Agreement&apos; tab for more details.</source>
        <translation>Подробности смотрите в закладке &quot;Лицензионное соглашениe&quot;.</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>Athens, Greece</source>
        <translation>Афины, Греция</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Tom Tryfonidis</source>
        <translation>Tom Tryfonidis</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Arch linux package/pkgbuild official maintainer (AUR)</source>
        <translation>официальный сопровождающий пакета в Arch linux</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Valuable advisor</source>
        <translation>ценный консультант</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Yiorgos Kapellakis</source>
        <translation>Yiorgos Kapellakis</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>rpm packager, valuable tester and remote connections advisor</source>
        <translation>сборщик пакетов rpm, ценный тестировщик и консультант по удалённым соединениям</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Patrick Matthaei</source>
        <translation>Patrick Matthaei</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Debian package maintainer</source>
        <translation>сопровождающий пакета в Debian</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Nikolas Poniros</source>
        <translation>Nikolas Poniros</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Greek gui translator and valuable tester</source>
        <translation>переводчик интерфейса на греческий и ценный тестировщик</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>The indifex team</source>
        <translation>Команда indifex</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>for developing the wonderful transifex localization platform and providing it for free</source>
        <translation>разработчики удобного и бесплатного сервиса Transifex для локализации приложений</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Stephan Kleine</source>
        <translation>Stephan Kleine</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>OpenSUSE package maintainer (KDE4 Community repo) and valuable packing advisor</source>
        <translation>сопровождающий пакета в OpenSUSE (репозиторий KDE4 Community) и ценный консультант по сборке пакетов</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Marcos Del Puerto Garcia</source>
        <translation>Marcos Del Puerto Garcia</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Mepis package maintainer (Community repo) &amp; Spanish gui translator</source>
        <translation>переводчик интерфейса на испанский и сопровождающий пакета для Mepis (Community repo)</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Savvas Radevic</source>
        <translation>Savvas Radevic</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>ubuntu package maintainer (launchpad PPA)</source>
        <translation>сопровождающий пакета в Ubuntu (launchpad PPA)</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Bruce Marriner</source>
        <translation>Bruce Marriner</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>port to MS Windows</source>
        <translation>портирование на MS Windows</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Juan Ramon Alfaro Martinez</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>Code contributor for remote &amp; vss support regarding the windows port</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+2"/>
        <source>Jack Fink</source>
        <translation>Jack Fink</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>port to Mac OS X</source>
        <translation>портирование на Mac OS X</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Elbert Pol</source>
        <translation>Elbert Pol</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>port to OS/2</source>
        <translation>портирование на OS/2</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Theo Chatzimichos</source>
        <translation>Theo Chatzimichos</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Gentoo ebuild maintainer</source>
        <translation>сопровождающий ebuild в Gentoo</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Dimitris Stasinopoulos</source>
        <translation>Dimitris Stasinopoulos</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Puppy pet &amp; sfs maintainer</source>
        <translation>сопровождающий pet и sfs в Puppy</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Juan Luis Baptiste</source>
        <translation>Juan Luis Baptiste</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Mandriva package maintainer (official contrib repo)</source>
        <translation>сопровождающий пакета в Mandriva (репозиторий contrib)</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Michael J Gruber</source>
        <translation>Michael J Gruber</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Jason E. Hale</source>
        <translation>Jason E. Hale</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Free BSD package maintainer</source>
        <translation>сопровождающий пакета для Free BSD</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Dimitris Jemos</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>Slackel package maintainer</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+3"/>
        <source>ex Fedora package maintainer</source>
        <translation>бывший сопровождающий пакета в Fedora</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Pavel Fric</source>
        <translation>Pavel Fric</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Czech gui translator</source>
        <translation>переводчик интерфейса на чешский</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Stergios Prosiniklis</source>
        <translation>Stergios Prosiniklis</translation>
    </message>
    <message>
        <location line="-63"/>
        <location line="+64"/>
        <source>Greek manual translator</source>
        <translation>переводчик руководства с греческого</translation>
    </message>
    <message>
        <location line="+3"/>
        <location line="+3"/>
        <location line="+3"/>
        <source>German gui translator</source>
        <translation>переводчик интерфейса на немецкий</translation>
    </message>
    <message>
        <location line="-4"/>
        <source>Wilfried Schobel</source>
        <translation>Wilfried Schobel</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Sergio Gameiro</source>
        <translation>Sergio Gameiro</translation>
    </message>
    <message>
        <location line="+1"/>
        <location line="+3"/>
        <source>Portuguese gui translator</source>
        <translation>переводчик интерфейса на португальский</translation>
    </message>
    <message>
        <location line="-1"/>
        <source>Marcio Moraes</source>
        <translation>Marcio Moraes</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Julien Cynober</source>
        <translation>Julien Cynober</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>French gui translator and valuable packing advisor (and not only)</source>
        <translation>переводчик интерфейса на французский и ценный советчик по сборке пакетов (и не только это)</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>Raffaele</source>
        <translation>Raffaele</translation>
    </message>
    <message>
        <location line="-2"/>
        <location line="+3"/>
        <location line="+3"/>
        <location line="+3"/>
        <source>Italian gui translator</source>
        <translation>переводчик интерфейса на итальянский</translation>
    </message>
    <message>
        <location line="-16"/>
        <source>Aurelien Merckel</source>
        <translation>Aurelien Merckel</translation>
    </message>
    <message>
        <location line="+18"/>
        <source>Denis Skorski</source>
        <translation>Denis Skorski</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Russian gui translator and valuable tester</source>
        <translation>переводчик интерфейса на русский и ценный тестировщик</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Kenny Verstraete</source>
        <translation>Kenny Verstraete</translation>
    </message>
    <message>
        <location line="+1"/>
        <location line="+3"/>
        <source>Dutch gui translator</source>
        <translation>переводчик интерфейса на нидерландский</translation>
    </message>
    <message>
        <location line="-1"/>
        <source>Martin Grashoff (linuxrev)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+3"/>
        <source>Subhi Honaco</source>
        <translation>Subhi Honaco</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Bosnian gui translator &amp; mandriva package maintainer</source>
        <translation>переводчик интерфейса на боснийский и сопровождающий пакета в Mandriva</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Majed Sahli</source>
        <translation>Majed Sahli</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Arabic gui translator</source>
        <translation>переводчик интерфейса на арабский</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Adrian Murariu</source>
        <translation>Adrian Murariu</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Romanian gui translator</source>
        <translation>переводчик интерфейса на румынский</translation>
    </message>
    <message>
        <location line="+20"/>
        <source>Roger Calvo</source>
        <translation>Roger Calvo</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Tomas Vadina</source>
        <translation>Tomas Vadina</translation>
    </message>
    <message>
        <location line="+18"/>
        <source>Javi Romero</source>
        <translation>Javi Romero</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>v0.3 gui designer</source>
        <translation>дизайнер интерфейса v.0.3</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>fri13</source>
        <translation>fri13</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>v.0.3 gui designer</source>
        <translation>дизайнер интерфейса v.0.3</translation>
    </message>
    <message>
        <location line="-151"/>
        <source>Dimitris Kalamaras</source>
        <translation>Dimitris Kalamaras</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>If it wasn&apos;t him and his tutorials I would never have started this project</source>
        <translation>если бы не было его и его руководств, я бы никогда не начал этот проект</translation>
    </message>
    <message>
        <location line="+59"/>
        <source>Thomas Glatt</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+13"/>
        <location line="+3"/>
        <source>French gui translator</source>
        <translation>переводчик интерфейса на французский</translation>
    </message>
    <message>
        <location line="-1"/>
        <source>Sébastien Bourgain</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+9"/>
        <source>pinguinofurioso</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+3"/>
        <source>Alessio Ganci</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+24"/>
        <source>Matej Urbančič</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+6"/>
        <source>Marvin Gomez</source>
        <translation>Marvin Gomez</translation>
    </message>
    <message>
        <location line="+1"/>
        <location line="+3"/>
        <source>Spanish gui translator</source>
        <translation>переводчик интерфейса на испанский</translation>
    </message>
    <message>
        <location line="-1"/>
        <source>Antonio Jose Molina</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+3"/>
        <source>Fredrik Holmgren</source>
        <translation>Fredrik Holmgren</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Swedish gui translator</source>
        <translation>переводчик интерфейса на шведский</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Catalan gui translator</source>
        <translation>переводчик интерфейса на каталонский</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Slovak gui translator</source>
        <translation>переводчик интерфейса на словацкий</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Rivo Zangov</source>
        <translation>Rivo Zangov</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Estonian gui translator</source>
        <translation>переводчик интерфейса на эстонский</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Nicolay Boychev</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>Bulgarian gui translator</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+2"/>
        <source>Manuel Meixide</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>Galician gui translator</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+2"/>
        <source>Roger Foss</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>Norwegian gui translator</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+2"/>
        <source>Pin-hsien Li</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>Chinese (Taiwan) gui translator</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+11"/>
        <source>Michele Dall&apos;Arno</source>
        <translation>Michele Dall&apos;Arno</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>special guest bug killer ;)</source>
        <translation>специально приглашённый убийца багов ;)</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Aphofis Scott</source>
        <translation>Aphofis Scott</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>valuable tester &amp; brainstorming specialist</source>
        <translation>ценный тестировщик и знаток мозгового штурма</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Yuri Vidal</source>
        <translation>Yuri Vidal</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>backupwhenidle python script developer</source>
        <translation>разработчик скрипта backupwhenidle на python</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Bjorn Rietdijk</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>valuable OS/2 and windows tester</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+2"/>
        <source>...to all users of the </source>
        <translation>... всем участникам</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>forums for their support.</source>
        <translation>форумов за их поддержку.</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Especially</source>
        <translation>Особенно</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>that contributed to this project one way or another</source>
        <translation>которые так или иначе внесли свой вклад в этот проект</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Last but no least</source>
        <translation>И последнее, но не менее важное</translation>
    </message>
    <message>
        <location line="+12"/>
        <source>Could not locate the license file</source>
        <translation>Файл с лицензией не найден</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>no money</source>
        <translation>Не деньгами</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>If you like this app and would like to donate something to me personally, all you have to do is:</source>
        <translation>Если вам понравилось приложение и вы захотели помочь проекту, то вы можете сделать следующее:</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Give a thumbs up at:</source>
        <translation>Рекомендовать приложение:</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Vote good &amp; become a fan at:</source>
        <translation>Проголосовать и стать фанатом:</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>This is my reward :)</source>
        <translation>Это будет моей наградой :)</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>money</source>
        <translation>Деньгами</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>I personally never had and never will accept money for this project.</source>
        <translation>Я никогда не брал и не буду брать деньги на проект.</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Nevertheless, I decided to use luckyBackup to support people that really need financial help.</source>
        <translation>Однако, я решил использовать luckyBackup, чтобы поддержать людей, которые действительно нуждаются в финансовой помощи.</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>So, please consider it seriously to donate money that will eventually be used for a good cause.</source>
        <translation>Подумайте о том, чтобы пожертвовать деньги на благое дело.</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>donation link</source>
        <translation>ссылка для пожертвований</translation>
    </message>
    <message>
        <location filename="../ui/about.ui" line="+14"/>
        <source>luckyBackup - about</source>
        <translation>luckyBackup - о программе</translation>
    </message>
    <message>
        <location line="+138"/>
        <source>close</source>
        <translation>Закрыть</translation>
    </message>
    <message>
        <location line="+20"/>
        <source>&amp;About</source>
        <translation>&amp;О проекте</translation>
    </message>
    <message>
        <location line="+12"/>
        <location line="+24"/>
        <location line="+24"/>
        <location line="+24"/>
        <location line="+24"/>
        <source>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:'GRArial'; font-size:10pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:&apos;DejaVu Sans&apos;; font-size:9pt;&quot;&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;GRArial&apos;; font-size:10pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:&apos;DejaVu Sans&apos;; font-size:9pt;&quot;&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location line="-12"/>
        <source>&amp;Support</source>
        <translation>&amp;Помощь</translation>
    </message>
    <message>
        <location line="-72"/>
        <source>A&amp;uthor</source>
        <translation>&amp;Автор</translation>
    </message>
    <message>
        <location line="+24"/>
        <source>&amp;Thanks to</source>
        <translation>&amp;Спасибо</translation>
    </message>
    <message>
        <location line="+24"/>
        <source>&amp;License Agreement</source>
        <translation>&amp;Лицензионное соглашение</translation>
    </message>
    <message>
        <location filename="../src/about.cpp" line="-253"/>
        <source>luckyBackup is distributed under the terms of the &lt;a href=&quot;http://www.gnu.org/copyleft/gpl.html&quot; target=&quot;_blank&quot;&gt;GNU General Public License&lt;/a&gt;</source>
        <comment>Please leave the tags &lt;a href=&quot;http://www.gnu.org/copyleft/gpl.html&quot; target=&quot;_blank&quot;&gt; &amp; &lt;/a&gt; intact and surrounding the GNU General Public License !!</comment>
        <translation>luckyBackup распространяется при соблюдении условий лицензии &lt;a href=&quot;http://www.gnu.org/copyleft/gpl.html&quot; target=&quot;_blank&quot;&gt;GNU General Public License&lt;/a&gt;</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>It is &lt;b&gt;free software&lt;/b&gt;: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 of the License.</source>
        <comment>Please leave tags eg &lt;b&gt;, &lt;/b&gt; intact and surrounding the words they are suppossed to !!</comment>
        <translation>Это &lt;b&gt;свободное программное обеспечение&lt;/b&gt;. Вы можете распространять и/или изменять его при соблюдении условий лицензии GNU General Public License (версии 3), опубликованной Фондом свободного программного обеспечения.</translation>
    </message>
    <message>
        <location line="+81"/>
        <source>Thomas Janssen</source>
        <translation>Thomas Janssen</translation>
    </message>
    <message>
        <location line="-8"/>
        <source>Fedora package maintainer (official repo)</source>
        <translation>сопровождающий пакета в Fedora (официальный репозиторий)</translation>
    </message>
    <message>
        <location line="+17"/>
        <source>Karsten Jaschultowski</source>
        <translation>Karsten Jaschultowski</translation>
    </message>
    <message>
        <location line="+24"/>
        <source>Francesco Braile</source>
        <translation>Francesco Braile</translation>
    </message>
    <message>
        <location line="+30"/>
        <source>Andrej Znidarsic</source>
        <translation>Andrej Znidarsic</translation>
    </message>
    <message>
        <location line="+1"/>
        <location line="+3"/>
        <source>Slovenian gui translator</source>
        <translation>переводчик интерфейса на словенский</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>E. Hakan Duran</source>
        <translation>E. Hakan Duran</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Turkish gui translator</source>
        <translation>переводчик интерфейса на турецкий</translation>
    </message>
    <message>
        <location line="+38"/>
        <source>Tito Poquito</source>
        <translation>Tito Poquito</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>slackware package maintainer (SlackBuilds Repository)</source>
        <translation>сопровождающий пакета в Slackware (репозиторий SlackBuilds)</translation>
    </message>
    <message>
        <location line="+26"/>
        <source>...my other half, &lt;b&gt;Dimitra&lt;/b&gt; that bears with me all these times that this project is under development</source>
        <translation>... моя вторая половинка &lt;b&gt;Dimitra&lt;/b&gt;, которая терпеливо относится ко мне все то время, пока я разрабатываю проект</translation>
    </message>
</context>
<context>
    <name>emailDialog</name>
    <message>
        <location filename="../ui/emailDialog.ui" line="+17"/>
        <source>luckyBackup - email</source>
        <translation>luckyBackup - оповещения</translation>
    </message>
    <message>
        <location line="+35"/>
        <source>Email a report after profile execution</source>
        <translation>Отправлять отчеты после выполнения задач профиля</translation>
    </message>
    <message>
        <location line="+17"/>
        <source>command:</source>
        <translation>команда:</translation>
    </message>
    <message>
        <location line="+38"/>
        <location line="+268"/>
        <location line="+14"/>
        <source>Use default</source>
        <extracomment>This means &quot;use the default value for this field&quot;
----------
This means &quot;use the default value for this field&quot;
----------
This means &quot;use the default value for this field&quot;</extracomment>
        <translation>По-умолчанию</translation>
    </message>
    <message>
        <location line="-218"/>
        <source>Arguments</source>
        <translation>Аргументы</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>%f from:</source>
        <translation>%f от кого:</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Enter the sender of the message</source>
        <translation>Адрес отправителя сообщения</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>%l logfile</source>
        <translation>%l лог-файл</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>%c logfile.tar.gz</source>
        <translation>%c лог-файл.tar.gz</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>%d date</source>
        <translation>%d дата</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>%i time</source>
        <translation>%i время</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>%p profile name</source>
        <translation>%p название профиля</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>%e No of errors</source>
        <translation>%e нет ошибок</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>If unchecked &quot;TLS auto&quot; is used. Only available for sendemail</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+3"/>
        <source>Disable TLS</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+25"/>
        <source>%t to:</source>
        <translation>%t кому:</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Enter the recipient of the message</source>
        <translation>Адрес получателя письма</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>%s subject:</source>
        <translation>%s тема:</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Enter the subject of the message</source>
        <translation>Тема письма</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>%v smtp server:</source>
        <translation>%v сервер SMTP:</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Enter the smtp server used to send the message</source>
        <translation>Адрес сервера SMTP для отправления писем</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>%b body:</source>
        <translation>%b содержание:</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Enter the body of the message</source>
        <translation>Содержание письма</translation>
    </message>
    <message>
        <location line="+56"/>
        <source>Send an email right now to test the provided arguments</source>
        <translation>Отправить письмо сейчас для проверки правильности аргументов</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Test</source>
        <translation>Проверка</translation>
    </message>
    <message>
        <location line="+24"/>
        <source>Accept changes and close dialog</source>
        <translation>Применить изменения и закрыть окно</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Okay</source>
        <translation>OK</translation>
    </message>
    <message>
        <location line="+27"/>
        <source>Close dialog</source>
        <translation>Закрыть окно</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Cancel</source>
        <translation>Отмена</translation>
    </message>
    <message>
        <location line="-348"/>
        <source>Specify the conditions to send an email</source>
        <translation>Укажите условия для отправления писем</translation>
    </message>
    <message>
        <location line="-38"/>
        <source>Enter the command to run
eg
sendemail</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+9"/>
        <source>arguments:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+7"/>
        <source>Enter arguments of the email command
eg
 -f %f -t %t -u &quot;%s&quot; -m &quot;%b&quot; -a %l -s %v</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+25"/>
        <source>Conditions</source>
        <translation>После выполнения отправить письмо</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Only send when error(s) occured during a run</source>
        <translation>Отправлять, только если во время выполнения произошли ошибки</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Error(s) occured</source>
        <translation>При ошибках выполнения</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Only send when profile is scheduled to run</source>
        <translation>Отправлять письма при выполнении профиля по расписанию</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Profile is scheduled</source>
        <translation>При выполнении по расписанию</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Never send an email</source>
        <translation>Никогда не отправлять сообщения</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Never</source>
        <translation>Никогда</translation>
    </message>
    <message>
        <location filename="../src/emailDialog.cpp" line="+136"/>
        <source>The command field is empty</source>
        <translation>Пустое поле для ввода команды</translation>
    </message>
</context>
<context>
    <name>helpBrowser</name>
    <message>
        <location filename="../ui/helpBrowser.ui" line="+14"/>
        <source>luckyBackup - help</source>
        <translation>luckyBackup - справка</translation>
    </message>
    <message>
        <location line="+16"/>
        <source>manual/</source>
        <translation>руководство/</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>Okay</source>
        <translation>OK</translation>
    </message>
</context>
<context>
    <name>logDialog</name>
    <message>
        <location filename="../ui/logDialog.ui" line="+14"/>
        <source>luckyBackup - tasks execution progress</source>
        <translation>luckyBackup - ход выполнения задач</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:'Greek Arial'; font-size:9pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:&apos;DejaVu Sans&apos;;&quot;&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;Greek Arial&apos;; font-size:9pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:&apos;DejaVu Sans&apos;;&quot;&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location line="+17"/>
        <source>previous error</source>
        <translation>Предыдущая ошибка</translation>
    </message>
    <message>
        <location line="+14"/>
        <source>next error</source>
        <translation>Следующая ошибка</translation>
    </message>
    <message>
        <location line="+27"/>
        <location filename="../src/logDialog.cpp" line="+86"/>
        <location line="+13"/>
        <source>close</source>
        <translation>Закрыть</translation>
    </message>
    <message>
        <location filename="../src/logDialog.cpp" line="-35"/>
        <source>loading logfile...</source>
        <translation>загрузка лог-файла...</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>wait</source>
        <translation>ждите</translation>
    </message>
</context>
<context>
    <name>luckyBackupWindow</name>
    <message>
        <location filename="../src/executenow.cpp" line="+161"/>
        <source>commands output</source>
        <comment>output window label</comment>
        <translation>Результат выполнения</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>rsync and pre/post task commands output is displayed here</source>
        <comment>tooltip</comment>
        <translation>Здесь выводятся результаты выполнения rsync и других команд</translation>
    </message>
    <message>
        <location line="+58"/>
        <location filename="../src/functions.cpp" line="+219"/>
        <source>Task list</source>
        <comment>task list label</comment>
        <translation>Список задач</translation>
    </message>
    <message>
        <location line="+1"/>
        <location filename="../src/functions.cpp" line="+2"/>
        <source>List of all the available tasks</source>
        <comment>task list tooltip - line1</comment>
        <translation>Список всех доступных задач</translation>
    </message>
    <message>
        <location line="+1"/>
        <location filename="../src/functions.cpp" line="+1"/>
        <source>Use the &apos;include checkboxes&apos; to include or not a selected task</source>
        <comment>task list tooltip - line2</comment>
        <translation>Используйте &quot;включающие отметки&quot; для включения или исключения выбранной задачи</translation>
    </message>
    <message>
        <location line="+35"/>
        <source>Execution of profile</source>
        <comment>full phrase: 'Execution of profile &lt;PROFILENAME&gt; finished'</comment>
        <translation>Выполнение профиля</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>finished</source>
        <comment>full phrase: 'Execution of profile &lt;PROFILENAME&gt; finished'</comment>
        <translation>завершено</translation>
    </message>
    <message>
        <location line="-173"/>
        <location line="+175"/>
        <location line="+1065"/>
        <location line="+21"/>
        <location line="+30"/>
        <location line="+1"/>
        <source>simulation mode</source>
        <translation>Тестовый режим</translation>
    </message>
    <message>
        <location line="-1113"/>
        <source>Could not update last execution time of tasks</source>
        <translation>Невозможно обновить время последнего выполнения</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Last execution time of tasks updated</source>
        <translation>Время последнего выполнения обновлено</translation>
    </message>
    <message>
        <location line="+33"/>
        <source>&amp;Abort</source>
        <translation>&amp;Прервать</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;Minimize to tray</source>
        <comment>tray menu action</comment>
        <translation>&amp;Свернуть в трей</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;Restore</source>
        <comment>tray menu action</comment>
        <translation>&amp;Восстановить</translation>
    </message>
    <message>
        <location line="-219"/>
        <source>execution of profile:</source>
        <comment>tray message - execution of profile: &lt;PROFILENAME&gt; in progress...</comment>
        <translation>Выполняется профиль:</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>in progress...</source>
        <comment>tray message - execution of profile: &lt;PROFILENAME&gt; in progress...</comment>
        <translation>...</translation>
    </message>
    <message>
        <location line="+451"/>
        <source>Removed all older snapshots data</source>
        <translation>Старые резервные копии удалены</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>failed to remove all older snapshots data</source>
        <translation>Не удалось удалить все старые резервные копии</translation>
    </message>
    <message>
        <location line="+520"/>
        <source>Unknown error</source>
        <translation>Неизвестная ошибка</translation>
    </message>
    <message>
        <location line="+253"/>
        <location line="+5"/>
        <location line="+6"/>
        <location line="+21"/>
        <location line="+27"/>
        <location line="+72"/>
        <source>Elapsed time</source>
        <translation>Затраченное время</translation>
    </message>
    <message>
        <location line="-130"/>
        <source>pre-task execution of command</source>
        <translation>Выполнение команд до выполнения задачи</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>post-task execution of command</source>
        <translation>Выполнение команд после выполнения задачи</translation>
    </message>
    <message>
        <location line="+6"/>
        <location line="+21"/>
        <source>Now performing task</source>
        <translation>Сейчас выполняется задача</translation>
    </message>
    <message>
        <location line="-14"/>
        <location line="+1"/>
        <source>Directory</source>
        <translation>Каталог</translation>
    </message>
    <message>
        <location line="+24"/>
        <source>calculating</source>
        <translation>вычисление</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>deleting files</source>
        <translation>удаление файлов</translation>
    </message>
    <message>
        <location line="+187"/>
        <source>trying to send an email</source>
        <translation>Попытка отправить сообщение</translation>
    </message>
    <message>
        <location line="+31"/>
        <source>The system will shutdown in 1 minute</source>
        <translation>Система будет перезагружена через 1 минуту</translation>
    </message>
    <message>
        <location line="-226"/>
        <source>Source</source>
        <translation>Источник</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Destination</source>
        <translation>Назначение</translation>
    </message>
    <message>
        <location line="+22"/>
        <location line="+1"/>
        <source>All tasks completed</source>
        <translation>Все задачи завершены</translation>
    </message>
    <message>
        <location line="+8"/>
        <location line="+1"/>
        <source>No errors found</source>
        <translation>Ошибок нет</translation>
    </message>
    <message>
        <location line="+4"/>
        <location line="+1"/>
        <source>errors found</source>
        <translation>Были обнаружены ошибки</translation>
    </message>
    <message>
        <location line="+8"/>
        <location line="+51"/>
        <source>logfile(s) have been created under directory: </source>
        <translation>лог-файлы сохранены в каталоге:</translation>
    </message>
    <message>
        <location filename="../src/functions.cpp" line="+21"/>
        <source>Done</source>
        <translation>Готово</translation>
    </message>
    <message>
        <location filename="../src/executenow.cpp" line="-38"/>
        <location line="+4"/>
        <location line="+48"/>
        <location line="+4"/>
        <source>execution of profile:</source>
        <translation>Выполнение профиля:</translation>
    </message>
    <message>
        <location line="-56"/>
        <location line="+4"/>
        <location line="+48"/>
        <location line="+4"/>
        <source>finished</source>
        <translation>завершено</translation>
    </message>
    <message>
        <location line="-22"/>
        <location line="+1"/>
        <source>Execution of tasks were terminated violently by user</source>
        <translation>Пользователь остановил выполнение задач профиля</translation>
    </message>
    <message>
        <location filename="../src/functions.cpp" line="-72"/>
        <source>&amp;Profile</source>
        <comment>This is a top menu item</comment>
        <translation>&amp;Профиль</translation>
    </message>
    <message>
        <location line="+28"/>
        <source>&amp;Settings</source>
        <comment>This is a top menu item</comment>
        <translation>&amp;Настройка</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>&amp;Language</source>
        <comment>This is a top menu item</comment>
        <translation>&amp;Язык</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>&amp;Help</source>
        <comment>This is a top menu item</comment>
        <translation>&amp;Справка</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;Handbook</source>
        <comment>full phrase: 'luckyBackup Handbook'</comment>
        <translation>&amp;руководство пользователя</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;About</source>
        <comment>full phrase: 'about luckyBackup'</comment>
        <translation>&amp;О программе</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>current profile</source>
        <translation>Текущий профиль</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>include</source>
        <comment>label of 'include' checkboxes</comment>
        <translation>Включить</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Move the highlighted task up, by one position</source>
        <comment>button tooltip</comment>
        <translation>Переместить выбранную задачу вверх на одну позицию</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Move the highlighted task down, by one position</source>
        <comment>button tooltip</comment>
        <translation>Переместить выбранную задачу вниз на одну позицию</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>jump to next error</source>
        <comment>button tooltip</comment>
        <translation>Следующая ошибка</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>jump to previous error</source>
        <comment>button tooltip</comment>
        <translation>Предыдущая ошибка</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Task</source>
        <comment>task groupbox (add, remove, modify buttons) label</comment>
        <translation>Задача</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>add</source>
        <comment>add task button label</comment>
        <translation>Добавить</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>add task</source>
        <comment>add task button tooltip</comment>
        <translation>Добавить задачу</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>remove</source>
        <comment>remove task button label</comment>
        <translation>Удалить</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>remove highlighted task</source>
        <comment>remove task button tooltip</comment>
        <translation>Удалить выбранную задачу</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>modify</source>
        <comment>modify task button label</comment>
        <translation>Изменить</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>modify highlighted task</source>
        <comment>modify task button tooltip</comment>
        <translation>Изменить выбранную задачу</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Begin the execution of all included tasks</source>
        <comment>start button tooltip</comment>
        <translation>Начать выполнение всех включенных задач</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>NOTE</source>
        <comment>simulation checkbox tooltip - line2</comment>
        <translation>ВНИМАНИЕ</translation>
    </message>
    <message>
        <location line="+0"/>
        <source>Progressbar update will not be realistic</source>
        <comment>simulation checkbox tooltip - line2</comment>
        <translation>Индикатор выполнения будет обновляться произвольно</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>Information window</source>
        <comment>information window title</comment>
        <translation>Информация</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Exit</source>
        <comment>exit button tooltip. full phrase is: 'exit luckybackup'</comment>
        <translation>Выход</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>EXIT</source>
        <comment>EXIT button label</comment>
        <translation>Выход</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>minimize to tray</source>
        <translation>Свернуть в трей</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>minimizes the window to the tray area</source>
        <translation>Свернуть окно в трей</translation>
    </message>
    <message>
        <location line="+43"/>
        <source>F1</source>
        <translation>F1</translation>
    </message>
    <message>
        <location line="+62"/>
        <source>English</source>
        <translation>Русский</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>&amp;%1 %2</source>
        <translation>&amp;%1 %2</translation>
    </message>
    <message>
        <location filename="../src/luckybackupwindow.cpp" line="+775"/>
        <source>You have asked for a RESTORE task to be created</source>
        <comment>'create restore' message line 1/4</comment>
        <translation>Вы запросили создание задачи &quot;Восстановление&quot;</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Please have a good look at the following task properties dialog</source>
        <comment>'create restore' message line 2/4</comment>
        <translation>Хорошо проверьте параметры задачи</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>and change anything you wish before proceeding</source>
        <comment>'create restore' message line 3/4</comment>
        <translation>и измените всё, что необходимо, в следующем диалоговом окне</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Especially check &apos;Task name&apos;, &apos;source&apos;, &apos;destination&apos; &amp; &apos;skip newer destination files&apos; checkbox (advanced)</source>
        <comment>'create restore' message line 4/4</comment>
        <translation>Обратите внимание на &apos;Название&apos;, &apos;Источник&apos;, &apos;Назначение&apos; и параметр &apos;Пропустить более новые файлы назначения&apos; (в расширенных настройках)</translation>
    </message>
    <message>
        <location filename="../src/functions.cpp" line="+86"/>
        <location filename="../src/luckybackupwindow.cpp" line="-432"/>
        <location line="+70"/>
        <location line="+14"/>
        <location line="+56"/>
        <location line="+85"/>
        <location line="+14"/>
        <location line="+238"/>
        <location line="+155"/>
        <location line="+269"/>
        <source>ERROR</source>
        <translation>ОШИБКА</translation>
    </message>
    <message>
        <location line="+83"/>
        <source>loading default profile ...</source>
        <comment>information window message</comment>
        <translation>Загрузка профиля по-умолчанию...</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>loading profile ...</source>
        <comment>information window message</comment>
        <translation>Загрузка профиля...</translation>
    </message>
    <message>
        <location line="+5"/>
        <location line="+8"/>
        <source>loading failed</source>
        <comment>information window message</comment>
        <translation>загрузка невозможна</translation>
    </message>
    <message>
        <location line="-7"/>
        <source>Unable to open profile</source>
        <comment>information window message. full phrase is 'Unable to open profile &lt;PROFIENAME&gt;'</comment>
        <translation>Невозможно открыть профиль</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>is not valid for</source>
        <comment>information window message. Full phrase is: 'profile &lt;PROFILENAME&gt; is not valid for luckybackup version:X.Y</comment>
        <translation>не совместим с</translation>
    </message>
    <message>
        <location line="+0"/>
        <source>version:</source>
        <comment>information window message. Full phrase is: 'profile &lt;PROFILENAME&gt; is not valid for luckybackup version:X.Y</comment>
        <translation>версии:</translation>
    </message>
    <message>
        <location line="+21"/>
        <source>profile</source>
        <comment>info window message. full phrase: 'profile &lt;PROFILENAME&gt; loaded successfully'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+0"/>
        <source>loaded successfully</source>
        <comment>info window message. full phrase: 'profile &lt;PROFILENAME&gt; loaded successfully'</comment>
        <translation>загружен успешно</translation>
    </message>
    <message>
        <location line="+10"/>
        <location line="+59"/>
        <source>scheduled</source>
        <comment>this refers to a profile</comment>
        <translation>есть расписание выполнения</translation>
    </message>
    <message>
        <location line="-54"/>
        <location line="+59"/>
        <source>YES</source>
        <translation>ДА</translation>
    </message>
    <message>
        <location line="-57"/>
        <location line="+59"/>
        <source>NO</source>
        <translation>НЕТ</translation>
    </message>
    <message>
        <location line="-51"/>
        <location line="+59"/>
        <source>Description</source>
        <translation>Описание</translation>
    </message>
    <message>
        <location line="-40"/>
        <source>saving default profile ...</source>
        <comment>Information window message</comment>
        <translation>Сохранение профиля по-умолчанию...</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>saving profile ...</source>
        <comment>Information window message</comment>
        <translation>Сохранение профиля...</translation>
    </message>
    <message>
        <location filename="../src/executenow.cpp" line="+132"/>
        <location filename="../src/functions.cpp" line="+4"/>
        <location line="+70"/>
        <source>WARNING</source>
        <translation>ПРЕДУПРЕЖДЕНИЕ</translation>
    </message>
    <message>
        <location filename="../src/functions.cpp" line="-68"/>
        <source>default profile</source>
        <comment>Information window message. Full phrase: 'default profile &lt;PROFILENAME&gt; could not be saved'.</comment>
        <translation>Профиль по-умолчанию</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>profile</source>
        <comment>Information window message. Full phrase: 'profile &lt;PROFILENAME&gt; could not be saved'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+8"/>
        <source>profile</source>
        <comment>Information window message. Full phrase: 'profile &lt;PROFILENAME&gt; saved successfully'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+0"/>
        <source>saved successfully</source>
        <comment>Information window message. Full phrase: 'profile &lt;PROFILENAME&gt; saved successfully'</comment>
        <translation>сохранен успешно</translation>
    </message>
    <message>
        <location line="+52"/>
        <source>creating default profile ...</source>
        <comment>Information window message</comment>
        <translation>Создание профиля по-умолчанию...</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>creating profile ...</source>
        <comment>Information window message</comment>
        <translation>Создание профиля...</translation>
    </message>
    <message>
        <location line="+13"/>
        <source>profile</source>
        <comment>Information window message. Full phrase: 'profile &lt;PROFILENAME&gt; created successfully'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+0"/>
        <source>created successfully</source>
        <comment>Information window message. Full phrase: 'profile &lt;PROFILENAME&gt; created successfully'</comment>
        <translation>создан успешно</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>Would you like to save it before proceeding ?</source>
        <translation>Сохранить изменения перед продолжением?</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Would you like to proceed anyway?</source>
        <translation>Всё равно продолжить?</translation>
    </message>
    <message>
        <location filename="../src/luckybackupwindow.cpp" line="-1159"/>
        <source>super user</source>
        <comment>super user is the root user</comment>
        <translation>суперпользователь</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>super user mode</source>
        <translation>режим суперпользователя</translation>
    </message>
    <message>
        <location line="+89"/>
        <source>Welcome to</source>
        <comment>full phrase: 'Welcome to luckyBackup'</comment>
        <translation>Добро пожаловать в</translation>
    </message>
    <message>
        <location line="+20"/>
        <source>English</source>
        <comment>Do not translate this. Enter here the language of the translation in native characters instead. This is how your translation will appear under the 'language' menu.</comment>
        <translation>Русский</translation>
    </message>
    <message>
        <location line="+121"/>
        <source>Failed to create new profile</source>
        <comment>full phrase: 'Failed to create new profile &lt;PROFILENAME&gt;'</comment>
        <translation>Невозможно создать новый профиль</translation>
    </message>
    <message>
        <location line="+2"/>
        <location line="+574"/>
        <source>The name you have entered contains only invalid characters</source>
        <translation>Введённое название содержит только недопустимые символы</translation>
    </message>
    <message>
        <location line="-560"/>
        <location line="+70"/>
        <location line="+156"/>
        <source>Profile</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; already exists'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="-225"/>
        <location line="+70"/>
        <location line="+156"/>
        <source>already exists</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; already exists'</comment>
        <translation>уже существует</translation>
    </message>
    <message>
        <location line="-225"/>
        <location line="+70"/>
        <location line="+156"/>
        <source>Would you like to replace it ?</source>
        <translation>Хотите заменить его?</translation>
    </message>
    <message>
        <location line="-216"/>
        <location line="+70"/>
        <location line="+155"/>
        <source>Failed to replace profile</source>
        <comment>full phrase: 'Failed to replace profile &lt;PROFILENAME&gt;'</comment>
        <translation>Невозможно заменить профиль</translation>
    </message>
    <message>
        <location line="-193"/>
        <location line="+52"/>
        <source>Failed to rename profile</source>
        <comment>full phrase: 'Failed to rename profile &lt;PROFILENAME&gt;'</comment>
        <translation>Невозможно переименовать профиль</translation>
    </message>
    <message>
        <location line="-43"/>
        <location line="+56"/>
        <source>profile</source>
        <comment>full phrase: 'profile &lt;PROFILENAME&gt; renamed successfully to &lt;NEWPROFILENAME&gt;'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="-54"/>
        <source>renamed successfully to</source>
        <comment>full phrase: 'profile &lt;PROFILENAME&gt; renamed successfully to &lt;NEWPROFILENAME&gt;'</comment>
        <translation>успешно переименован в</translation>
    </message>
    <message>
        <location line="+49"/>
        <source>default profile</source>
        <comment>full phrase: 'default profile &lt;PROFILENAME&gt; renamed successfully to &lt;NEWPROFILENAME&gt;'.</comment>
        <translation>Профиль по-умолчанию</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>renamed successfully to</source>
        <comment>full phrase: '(default) profile &lt;PROFILENAME&gt; renamed successfully to &lt;NEWPROFILENAME&gt;'</comment>
        <translation>успешно переименован в</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>All relevant files (logs etc) have also been updated</source>
        <translation>Все необходимые файлы (логи т.д.) также были обновлены</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Failed to update all relevant files (logs etc)</source>
        <translation>Не удалось обновить все необходимые файлы (логи и т.д.)</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>Are you sure you want to delete the default profile</source>
        <comment>full phrase: 'Are you sure you want to delete the default profile: &lt;PROFILENAME&gt; ? (a new blank one, with the same name, will be created)'</comment>
        <translation>Вы уверены, что хотите удалить профиль по-умолчанию</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>a new blank one, with the same name, will be created</source>
        <comment>full phrase: 'Are you sure you want to delete the default profile: &lt;PROFILENAME&gt; ? (a new blank one, with the same name, will be created)'</comment>
        <translation>будет создан новый пустой профиль с таким же названием</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Are you sure you want to delete profile</source>
        <comment>full phrase: 'Are you sure you want to delete profile: &lt;PROFILENAME&gt; ?'</comment>
        <translation>Вы уверены, что хотите удалить профиль</translation>
    </message>
    <message>
        <location line="+13"/>
        <source>Failed to delete profile</source>
        <comment>full phrase: 'Failed to delete profile &lt;PROFILENAME&gt;'</comment>
        <translation>Невозможно удалить профиль</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Profile</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; deleted successfully'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>deleted successfully</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; deleted successfully'</comment>
        <translation>удален успешно</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>All relevant files (logs etc) have also been deleted</source>
        <translation>Все необходимые файлы (логи и т.д.) также были удалены</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Failed to delete all relevant files (logs etc)</source>
        <translation>Невозможно удалить все все необходимые файлы (логи и т.д.)</translation>
    </message>
    <message>
        <location line="+26"/>
        <source>Profile</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; set as default'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+0"/>
        <source>set as default</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; set as default'</comment>
        <translation>установлен как профиль по-молчанию</translation>
    </message>
    <message>
        <location line="+75"/>
        <source>All relevant files (logs etc) have also been duplicated</source>
        <translation>Все необходимые файлы (логи и т.д.) также были скопированы</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Failed to duplicate all relevant files (logs etc)</source>
        <translation>Невозможно скопировать все необходимые файлы (логи и т.д.)</translation>
    </message>
    <message>
        <location line="+26"/>
        <source>The description of profile</source>
        <comment>full phrase: 'The description of profile &lt;PROFILENAME&gt; set to: &lt;DESCRIPTION&gt;'</comment>
        <translation>Описание профиля</translation>
    </message>
    <message>
        <location line="+0"/>
        <source>set to</source>
        <comment>full phrase: 'The description of profile &lt;PROFILENAME&gt; set to: &lt;DESCRIPTION&gt;'</comment>
        <translation>установлено как</translation>
    </message>
    <message>
        <location line="+220"/>
        <source>Import Profile</source>
        <comment>this is a dialog title</comment>
        <translation>Импорт профиля</translation>
    </message>
    <message>
        <location line="+13"/>
        <location line="+29"/>
        <location line="+33"/>
        <source>Failed to import profile</source>
        <comment>full phrase: 'Failed to import profile &lt;PROFILENAME&gt;'</comment>
        <translation>Невозможно импортировать профиль</translation>
    </message>
    <message>
        <location line="-17"/>
        <source>Profile</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; imported successfully as &lt;NEWPROFILENAME&gt; and added at the profile list'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>imported successfully</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; imported successfully as &lt;NEWPROFILENAME&gt; and added at the profile list'</comment>
        <translation>был импортирован успешно</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>as</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; imported successfully as &lt;NEWPROFILENAME&gt; and added at the profile list'</comment>
        <translation>как</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>and added at the profile list</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; imported successfully as &lt;NEWPROFILENAME&gt; and added at the profile list'</comment>
        <translation>и добавлен в список профилей</translation>
    </message>
    <message>
        <location line="+63"/>
        <source>Could not locate the file</source>
        <comment>full phrase: 'Could not locate the file &lt;FILENAME&gt;'</comment>
        <translation>Невозможно найти файл</translation>
    </message>
    <message>
        <location line="-319"/>
        <location line="+64"/>
        <location line="+293"/>
        <source>You have reached the maximum limit of supported tasks</source>
        <translation>Достигнуто максимальное количество задач</translation>
    </message>
    <message>
        <location line="-356"/>
        <location line="+64"/>
        <location line="+293"/>
        <source>You have to remove a task if you wish to add another !!</source>
        <translation>Удалите какую-либо задачу, чтобы добавить новую!!</translation>
    </message>
    <message>
        <location line="-208"/>
        <source>Select export directory</source>
        <comment>this is a dialog title for selecting a directory to export a profile to</comment>
        <translation>Выберите каталог для экспорта</translation>
    </message>
    <message>
        <location line="+14"/>
        <source>Failed to export profile</source>
        <comment>full phrase: 'Failed to export profile &lt;PROFILENAME&gt; to &lt;DIRNAME&gt;'</comment>
        <translation>Невозможно экспортировать профиль</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>to</source>
        <comment>full phrase: 'Failed to export profile &lt;PROFILENAME&gt; to &lt;DIRNAME&gt;'</comment>
        <translation>в каталог</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Profile</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; exported successfully to &lt;DIRNAME&gt;'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>exported successfully to</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; exported successfully to &lt;DIRNAME&gt;'</comment>
        <translation>успешно экспортирован в каталог</translation>
    </message>
    <message>
        <location line="+31"/>
        <source>The directory you have selected does not contain valid profile data</source>
        <translation>Выбранный каталог не содержит данных профиля</translation>
    </message>
    <message>
        <location line="+53"/>
        <source>Errors occured during snapshots and logfiles transfer</source>
        <translation>При импортировании резервных копий и лог-файлов произошли ошибки</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Errors occured during snapshots transfer</source>
        <translation>При импортировании резервных копий произошли ошибки</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Errors occured during logfiles transfer</source>
        <translation>При импортировании лог-файлов произошли ошибки</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Errors occured during the profile file transfer</source>
        <translation>При импортировании файлов профиля произошли ошибки</translation>
    </message>
    <message>
        <location line="+123"/>
        <source>Please select a task to modify first</source>
        <translation>Выберите задачу, которую необходимо изменить</translation>
    </message>
    <message>
        <location line="+55"/>
        <source>Please select a task to remove first</source>
        <translation>Выберите задачу, которую необходимо удалить</translation>
    </message>
    <message>
        <location line="+8"/>
        <source>Are you sure you want to remove the following task ??</source>
        <translation>Вы уверены, что хотите удалить следующую задачу ??</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Would you like to also remove:</source>
        <translation>Удалить также задачу для восстановления:</translation>
    </message>
    <message>
        <location line="+51"/>
        <source>Please select a task to manage first</source>
        <translation>Выберите задачу, которую необходимо просмотреть</translation>
    </message>
    <message>
        <location line="+80"/>
        <source>nothing to do</source>
        <translation>Сижу, курю</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>current crontab &lt;font color=green&gt;updated successfully</source>
        <translation>Файл crontab &lt;font color=green&gt;успешно обновлён</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>Email preferences have been &lt;font color=green&gt;updated successfully</source>
        <translation>Настройки оповещений &lt;font color=green&gt;успешно обновлены</translation>
    </message>
    <message>
        <location line="+76"/>
        <source>status</source>
        <translation>Состояние</translation>
    </message>
    <message>
        <location line="+0"/>
        <source>NOT INCLUDED</source>
        <translation>НЕ ВКЛЮЧЕНА</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Checks are disabled. This task will be &lt;b&gt;skipped&lt;/b&gt;</source>
        <translation>Проверки отключены. Эта задача &lt;b&gt;будет пропущена&lt;/b&gt;</translation>
    </message>
    <message>
        <location line="+33"/>
        <source>Task list of profile</source>
        <comment>full phrase: 'Task list of profile &lt;PROFILENAME&gt; and 'profile' drop-down list refreshed'</comment>
        <translation>Список задач профиля</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>and &apos;profile&apos; drop-down list</source>
        <comment>full phrase: 'Task list of profile &lt;PROFILENAME&gt; and 'profile' drop-down list refreshed'</comment>
        <translation>и список профилей</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>refreshed</source>
        <comment>full phrase: 'Task list of profile &lt;PROFILENAME&gt; and 'profile' drop-down list refreshed'</comment>
        <translation>обновлены</translation>
    </message>
    <message>
        <location filename="../ui/luckybackupwindow.ui" line="+39"/>
        <source>luckyBackup</source>
        <translation>luckyBackup</translation>
    </message>
    <message>
        <location line="+976"/>
        <source>Ctrl+S</source>
        <translation>Ctrl+S</translation>
    </message>
    <message>
        <location line="-369"/>
        <source>Information window</source>
        <translation>Информация</translation>
    </message>
    <message>
        <location line="-396"/>
        <source>CheckBox</source>
        <translation>CheckBox</translation>
    </message>
    <message>
        <location line="+430"/>
        <source>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:'Bitstream Vera Sans'; font-size:10pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:&apos;DejaVu Sans&apos;; font-size:9pt;&quot;&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;Bitstream Vera Sans&apos;; font-size:10pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:&apos;DejaVu Sans&apos;; font-size:9pt;&quot;&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location line="+176"/>
        <source>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:'Bitstream Vera Sans'; font-size:10pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:&apos;DejaVu Sans&apos;; font-size:9pt;&quot;&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;Bitstream Vera Sans&apos;; font-size:10pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:&apos;DejaVu Sans&apos;; font-size:9pt;&quot;&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location line="+27"/>
        <source>&amp;Profile</source>
        <translation>&amp;Профиль</translation>
    </message>
    <message>
        <location line="+45"/>
        <source>Ctrl+N</source>
        <translation>Ctrl+N</translation>
    </message>
    <message>
        <location line="+33"/>
        <source>Ctrl+X</source>
        <translation>Ctrl+X</translation>
    </message>
    <message>
        <location line="+33"/>
        <source>Ctrl+D</source>
        <translation>Ctrl+D</translation>
    </message>
    <message>
        <location line="+33"/>
        <source>F5</source>
        <translation>F5</translation>
    </message>
    <message>
        <location filename="../src/executenow.cpp" line="-1295"/>
        <source>Aborting: Please wait for all processes to be killed</source>
        <translation>Прерывание: подождите, пока завершатся все процессы</translation>
    </message>
    <message>
        <location line="+197"/>
        <source>Removing old snapshots and logfiles of task</source>
        <comment>info message displayed during ...data removal
Full phrase: Removing old snapshots and logfiles of task: &lt;TASKNAME&gt;</comment>
        <translation>Удаление старых резервных копий и лог-файлов</translation>
    </message>
    <message>
        <location line="+73"/>
        <location line="+12"/>
        <source>Removing</source>
        <translation>Удаление</translation>
    </message>
    <message>
        <location line="-10"/>
        <location line="+12"/>
        <source>failed to remove</source>
        <translation>Невозможно переместить</translation>
    </message>
    <message>
        <location line="+495"/>
        <source>Failed to start</source>
        <comment>this refers to a process</comment>
        <translation>Невозможно запустить</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Crashed</source>
        <comment>this refers to a process</comment>
        <translation>Аварийная остановка</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Timed out</source>
        <comment>this refers to a process</comment>
        <translation>Превышено время</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Write error</source>
        <comment>this refers to a process</comment>
        <translation>Ошибка записи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Read error</source>
        <comment>this refers to a process</comment>
        <translation>Ошибка чтения</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Unknown error</source>
        <comment>this refers to a process</comment>
        <translation>Неизвестная ошибка</translation>
    </message>
    <message>
        <location line="+263"/>
        <source>calculating</source>
        <comment>info message displayed during ...calculations</comment>
        <translation>Вычисление</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>transferring files</source>
        <comment>info message displayed during ...file transfers</comment>
        <translation>передача файлов</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>deleting files</source>
        <comment>info message displayed during ...file deletions</comment>
        <translation>удаление файлов</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>transferring files</source>
        <translation>передача файлов</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>Total files transfered</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+81"/>
        <source>ABORTED</source>
        <translation>Выполнение ПРЕРВАНО</translation>
    </message>
    <message>
        <location filename="../src/functions.cpp" line="-560"/>
        <source>&amp;Refresh</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>&amp;Обновить</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>De&amp;fault</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>&amp;Установить по умолчанию</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Set as Default</source>
        <comment>This is a top 'Profile' menu action tooltip</comment>
        <translation>Установить как профиль по-умолчанию</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;View/Edit Description</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>Р&amp;едактировать описание</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>View/Edit the profile description</source>
        <comment>This is a top 'Profile' menu action tooltip</comment>
        <translation>Просмотреть или отредактировать описание профиля</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>R&amp;ename</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>&amp;Переименовать</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;Delete</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>&amp;Удалить</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;New</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>&amp;Новый</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;Save</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>&amp;Сохранить</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>E&amp;xport</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>&amp;Экспорт</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;Import</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>&amp;Импорт</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>S&amp;chedule</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>&amp;Расписание</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>E&amp;mail</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>Опо&amp;вещения</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Email report after profile execution</source>
        <comment>This is a top 'Profile' menu action tooltip</comment>
        <translation>Отправить письмо после выполнения задач профиля</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;Quit</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>&amp;Выход</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>D&amp;uplicate</source>
        <comment>This is a top 'Profile' menu action</comment>
        <translation>Создать &amp;копию</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>&amp;Task</source>
        <comment>This is a top menu action</comment>
        <translation>&amp;Задача</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;Add</source>
        <comment>This is a top 'Task' menu action</comment>
        <translation>&amp;Добавить</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;Remove</source>
        <comment>This is a top 'Task' menu action</comment>
        <translation>&amp;Удалить</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>&amp;Modify</source>
        <comment>This is a top 'Task' menu action</comment>
        <translation>&amp;Изменить</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Create D&amp;uplicate task</source>
        <comment>This is a top 'Task' menu action</comment>
        <translation>Создать &amp;копию задачи</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Create R&amp;estore task</source>
        <comment>This is a top 'Task' menu action</comment>
        <translation>Создать задачу для &amp;восстановления</translation>
    </message>
    <message>
        <location line="+1"/>
        <location filename="../src/luckybackupwindow.cpp" line="-45"/>
        <source>Manage &amp;Backup</source>
        <comment>This is a top 'Task' menu action</comment>
        <translation>&amp;Список резервных копий</translation>
    </message>
    <message>
        <location line="+1"/>
        <location filename="../src/luckybackupwindow.cpp" line="+1"/>
        <source>display - restore - delete existing backups of highlighted task</source>
        <comment>This is a top 'Task' menu action tooltip</comment>
        <translation>Просмотреть, восстановить или удалить резервные копии выделенной задачи</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Actions</source>
        <comment>This is a top menu action</comment>
        <translation>Действия</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Current Profile</source>
        <comment>This is a top menu action</comment>
        <translation>Текущий профиль</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Lock</source>
        <comment>This is a top menu action. Refers to toolbars</comment>
        <translation>Заблокировать панели инструментов</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Show text under icons</source>
        <comment>This is a top menu action</comment>
        <translation>Показывать текст под значками</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>&amp;Toolbars</source>
        <comment>This is a top menu item</comment>
        <translation>&amp;Панели инструментов</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Set paths</source>
        <comment>This is a top menu action</comment>
        <translation>Пути</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Set paths for rsync and ssh commands</source>
        <comment>This is a top menu action tooltip</comment>
        <translation>Указать пути к исполняемым файлам rsync и ssh</translation>
    </message>
    <message>
        <location line="+17"/>
        <source>quiet mode</source>
        <translation>Тихий режим</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Only show errors and important messages during window update</source>
        <translation>Показывать только важные сообщения и сообщения об ошибках</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>Run</source>
        <comment>start button label</comment>
        <translation>Выполнить</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Abort</source>
        <comment>Abort button label</comment>
        <translation>Прервать</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Stop the execution of running tasks NOW</source>
        <comment>Abort button tooltip</comment>
        <translation>Прервать выполнение запущенных задач</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Execution of tasks finished</source>
        <comment>Done button tooltip</comment>
        <translation>Задачи завершены</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Dry</source>
        <comment>simulation checkbox label. Translate this as 'simulation'</comment>
        <translation>Тест</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>This will perform a &lt;b&gt;simulation run&lt;/b&gt; that doesn&apos;t make any changes (and produces mostly the same output as a real run)</source>
        <comment>simulation checkbox tooltip - line1. Please leave tags &lt;b&gt; and &lt;/b&gt; intact and surrounding 'simulation run'</comment>
        <translation>Будет выполнен &lt;b&gt;тестовый запуск&lt;/b&gt; без сохранения изменений (хотя результат выполнения будет почти таким же, как и при настоящем запуске)</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>shutdown</source>
        <comment>shutdown button label</comment>
        <translation>Выключение</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Press down to shutdown the system when done</source>
        <comment>shutdown button tooltip</comment>
        <translation>Выключение компьютера после выполнения всех задач</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Hide information window</source>
        <comment>show/hide information window button tooltip</comment>
        <translation>Свернуть окно с информацией</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Show information window</source>
        <comment>show/hide information window button tooltip</comment>
        <translation>Показать окно с информацией</translation>
    </message>
    <message>
        <location line="+295"/>
        <source>profile </source>
        <comment>information window message. Full phrase is: 'profile &lt;PROFILENAME&gt; is not valid for luckybackup version:X.Y'. BEWARE of the whitespace in the end</comment>
        <translation>Профиль </translation>
    </message>
    <message>
        <location line="+52"/>
        <source>The task list is empty</source>
        <translation>Список задач пустой</translation>
    </message>
    <message>
        <location line="+0"/>
        <location line="+100"/>
        <source>Use the &quot;add&quot; button on the right to get started</source>
        <comment>Please keep the add word inside quotes</comment>
        <translation>Для начала работы нажмите справа кнопку &quot;Добавить&quot;</translation>
    </message>
    <message>
        <location line="-74"/>
        <source>could not be saved</source>
        <comment>Information window message. Full phrase: '(default) profile &lt;PROFILENAME&gt; could not be saved'</comment>
        <translation>не может быть сохранён</translation>
    </message>
    <message>
        <location line="+66"/>
        <source>default profile</source>
        <comment>Information window message. Full phrase: 'default profile &lt;PROFILENAME&gt; could not be created'.</comment>
        <translation>Профиль по-умолчанию</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>could not be created</source>
        <comment>Information window message. Full phrase: '(default) profile &lt;PROFILENAME&gt; could not be created'</comment>
        <translation>не может быть создан</translation>
    </message>
    <message>
        <location line="+21"/>
        <source>Profile</source>
        <comment>Question dialog message. Full phrase: 'profile &lt;PROFILENAME&gt; is modified'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>is modified</source>
        <comment>Question dialog message. Full phrase: 'profile &lt;PROFILENAME&gt; is modified'</comment>
        <translation>изменён</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Profile</source>
        <comment>Question dialog message. Full phrase: 'profile &lt;PROFILENAME&gt; could not be saved'</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+0"/>
        <source>could not be saved</source>
        <comment>Question dialog message. Full phrase: 'profile &lt;PROFILENAME&gt; could not be saved'</comment>
        <translation>не может быть сохранён</translation>
    </message>
    <message>
        <location line="-32"/>
        <source>profile</source>
        <comment>Information window message. Full phrase: 'profile &lt;PROFILENAME&gt; could not be created'.</comment>
        <translation>Профиль</translation>
    </message>
    <message>
        <location filename="../src/luckybackupwindow.cpp" line="-808"/>
        <source>Failed to duplicate profile</source>
        <comment>full phrase: 'Failed to duplicate profile &lt;PROFILENAME&gt;'</comment>
        <translation>Невозможно создать копию профиля</translation>
    </message>
    <message>
        <location line="+41"/>
        <source>Failed to duplicate profile</source>
        <comment>full phrase: 'Failed to duplicate profile &lt;PROFILENAME&gt; as &lt;FILENAME&gt;'</comment>
        <translation>Невозможно создать копию профиля</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>as</source>
        <comment>full phrase: 'Failed to duplicate profile &lt;PROFILENAME&gt; as &lt;FILENAME&gt;'</comment>
        <translation>с названием</translation>
    </message>
    <message>
        <location line="+8"/>
        <source>Profile</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; duplicated successfully as &lt;FILENAME&gt;'</comment>
        <translation>Копия профиля</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>duplicated successfully as</source>
        <comment>full phrase: 'Profile &lt;PROFILENAME&gt; duplicated successfully as &lt;FILENAME&gt;'</comment>
        <translation>создана успешно и называется</translation>
    </message>
    <message>
        <location line="+52"/>
        <source>Please select a task to duplicate first</source>
        <translation>Выберите задачу, которую необходимо скопировать</translation>
    </message>
    <message>
        <location line="+65"/>
        <source>Please select a task first</source>
        <translation>Выберите задачу</translation>
    </message>
    <message>
        <location line="+238"/>
        <source>Hide information window</source>
        <comment>hide/show information window button tooltip</comment>
        <translation>Свернуть окно с информацией</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Show information window</source>
        <comment>hide/show information window button tooltip</comment>
        <translation>Показать окно с информацией</translation>
    </message>
    <message>
        <location line="+287"/>
        <source>You have only included tasks that are going to be skipped</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+96"/>
        <source>Manage Task</source>
        <comment>This is a top 'Task' menu action</comment>
        <translation>Сведения о задаче</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>display information regarding highlighted task</source>
        <comment>This is a top 'Task' menu action tooltip</comment>
        <translation>Показать сведения о выделенной задаче</translation>
    </message>
    <message>
        <location filename="../ui/luckybackupwindow.ui" line="-122"/>
        <source>&amp;Task</source>
        <translation>&amp;Задача</translation>
    </message>
    <message>
        <location filename="../src/executenow.cpp" line="-631"/>
        <source>Successfuly created destination directory</source>
        <translation>Каталог назначения успешно создан</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Failed to create destination directory</source>
        <translation>Невозможно создать каталог назанчения</translation>
    </message>
</context>
<context>
    <name>manageDialog</name>
    <message>
        <location filename="../src/manage.cpp" line="+95"/>
        <source>profile</source>
        <translation>Профиль</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>task</source>
        <translation>Задача</translation>
    </message>
    <message>
        <location filename="../ui/manage.ui" line="+234"/>
        <source>Delete</source>
        <translation>Удалить</translation>
    </message>
    <message>
        <location line="+26"/>
        <source>Restore</source>
        <translation>Восстановить</translation>
    </message>
    <message>
        <location line="+23"/>
        <source>view log</source>
        <translation>Лог-файл</translation>
    </message>
    <message>
        <location line="-186"/>
        <source>destination:</source>
        <translation>Назначение:</translation>
    </message>
    <message>
        <location line="+31"/>
        <source>source:</source>
        <translation>Источник:</translation>
    </message>
    <message>
        <location line="+175"/>
        <source>hide source</source>
        <translation>Скрыть Источник</translation>
    </message>
    <message>
        <location line="-130"/>
        <source>Close this window</source>
        <translation>Закрыть окно</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Close</source>
        <translation>Закрыть</translation>
    </message>
    <message>
        <location filename="../src/manage.cpp" line="+135"/>
        <source>Please select a snapshot from the list</source>
        <comment>Information message</comment>
        <translation>Выберите резервную копию из списка</translation>
    </message>
    <message>
        <location line="+146"/>
        <source>This directory does not exist</source>
        <translation>Каталог Источник не существует</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>This directory does not exist</source>
        <comment>Information message</comment>
        <translation>Каталог Назначение не существует</translation>
    </message>
    <message>
        <location line="+10"/>
        <location line="+8"/>
        <source>I do not have sufficient permissions to read this directory</source>
        <comment>Information message</comment>
        <translation>Нет прав для чтения этого каталога</translation>
    </message>
    <message>
        <location line="+13"/>
        <source>sync dir A</source>
        <comment>full phrase: sync dir a: &lt;DIRECTORY_A&gt;</comment>
        <translation>Каталог A</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>sync dir B</source>
        <comment>full phrase: sync dir a: &lt;DIRECTORY_b&gt;</comment>
        <translation>Каталог B</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>View the logfile of the selected sync task</source>
        <comment>'view log' pushbutton tooltip</comment>
        <translation>Показать лог-файл выбранной синхронизации</translation>
    </message>
    <message>
        <location line="+83"/>
        <source>Please wait until the thread is terminated</source>
        <translation>Подождите, пока выполняется программа</translation>
    </message>
    <message>
        <location line="+24"/>
        <source>STOP</source>
        <translation>ОСТАНОВИТЬ</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Stop calculations NOW</source>
        <translation>Остановить вычисление СЕЙЧАС</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>Calculations terminated by user</source>
        <translation>Вычисление отменено пользователем</translation>
    </message>
    <message>
        <location line="+59"/>
        <location line="+12"/>
        <source>not available</source>
        <comment>refers to a date-time</comment>
        <translation>не доступно</translation>
    </message>
    <message>
        <location filename="../ui/manage.ui" line="-159"/>
        <source>luckyBackup - manage backup</source>
        <translation>luckyBackup - резервные копии</translation>
    </message>
    <message>
        <location line="+214"/>
        <source>Delete the selected snapshot and its logfile</source>
        <translation>Удалить выбранную резервную копию и её лог-файлы</translation>
    </message>
    <message>
        <location line="+26"/>
        <source>Restore the selected snapshot</source>
        <translation>Восстановить выбранную резервную копию</translation>
    </message>
    <message>
        <location line="+23"/>
        <source>View the logfile of the selected snapshot</source>
        <translation>Показать лог-файл выбранной резервной копии</translation>
    </message>
    <message>
        <location line="+33"/>
        <location filename="../src/manage.cpp" line="-57"/>
        <source>Calculate the differences between the source and the selected snapshot</source>
        <translation>Показать различия между Источником и выбранной резервной копией</translation>
    </message>
    <message>
        <location line="+3"/>
        <location filename="../src/manage.cpp" line="-1"/>
        <source>Calculate differences</source>
        <translation>Показать различия</translation>
    </message>
</context>
<context>
    <name>manageWizard</name>
    <message>
        <location filename="../src/manageWizard.cpp" line="+60"/>
        <source>not available</source>
        <comment>refers to a date-time</comment>
        <translation>не доступно</translation>
    </message>
    <message>
        <location line="+361"/>
        <source>Delete backup</source>
        <comment>this is the title of a wizard</comment>
        <translation>Удаление резервной копии</translation>
    </message>
    <message>
        <location line="+1"/>
        <location line="+16"/>
        <source>Date &amp; time</source>
        <comment>simple label of the wizard gui</comment>
        <translation>Дата и время</translation>
    </message>
    <message>
        <location line="-15"/>
        <source>Path</source>
        <comment>...is a directory path</comment>
        <translation>Путь</translation>
    </message>
    <message>
        <location line="-285"/>
        <location line="+286"/>
        <source>WARNING</source>
        <translation>ПРЕДУПРЕЖДЕНИЕ</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>You are about to delete backup data</source>
        <comment>information message - line1</comment>
        <translation>Вы собираетесь удалить резервную копию</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>If the information above is correct, click &lt;b&gt;start&lt;/b&gt; to begin</source>
        <comment>information message - line2.
Please leave tags &lt;b&gt;&lt;/b&gt; intact and surrounding 'start' translated</comment>
        <translation>Если приведенная выше информация правильная, нажмите кнопку &lt;b&gt;Начать&lt;/b&gt;</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>Restore backup</source>
        <comment>this is the title of a wizard</comment>
        <translation>Восстановление из резервной копии</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Backup path</source>
        <comment>...is the backup directory path</comment>
        <translation>Каталог резервной копии</translation>
    </message>
    <message>
        <location line="-194"/>
        <source>close</source>
        <translation>Закрыть</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>Deleting snapshot logfile</source>
        <comment>info message displayed during ...logfile deletion</comment>
        <translation>Удаление лог-файла</translation>
    </message>
    <message>
        <location line="+28"/>
        <source>Updating list of snapshots</source>
        <comment>info message displayed during ...snaps list update</comment>
        <translation>Обновление списка резервных копий</translation>
    </message>
    <message>
        <location line="+22"/>
        <source>Aborted</source>
        <translation>Прервано</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Finished</source>
        <translation>Завершено</translation>
    </message>
    <message>
        <location filename="../ui/manageWizard.ui" line="+240"/>
        <location filename="../src/manageWizard.cpp" line="+3"/>
        <location line="+235"/>
        <source>simulation</source>
        <translation>Тест</translation>
    </message>
    <message>
        <location filename="../src/manageWizard.cpp" line="-230"/>
        <source>no errors</source>
        <translation>Ошибок нет</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>errors found</source>
        <translation>Были обнаружены ошибки</translation>
    </message>
    <message>
        <location line="+220"/>
        <source>Restoring data: main trunk</source>
        <comment>info message displayed during ...data restoration</comment>
        <translation>Восстановление файлов: основная операция</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Restoring data: snapshot files</source>
        <comment>info message displayed during ...data restoration</comment>
        <translation>Восстановление файлов: резервная копия</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Deleting data</source>
        <comment>info message displayed during ...data deletion</comment>
        <translation>Удаление файлов</translation>
    </message>
    <message>
        <location filename="../ui/manageWizard.ui" line="-226"/>
        <source>luckyBackup - manage backup</source>
        <translation>luckyBackup - резервные копии</translation>
    </message>
    <message>
        <location line="+182"/>
        <source>Jump to previous error</source>
        <translation>Предыдущая ошибка</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>previous error</source>
        <translation>Предыдущая ошибка</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>Jump to next error</source>
        <translation>Следующая ошибка</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>next error</source>
        <translation>Следующая ошибка</translation>
    </message>
    <message>
        <location line="+24"/>
        <source>This will perform a &lt;b&gt;simulation run&lt;/b&gt; that doesn&apos;t make any changes (and produces mostly the same output as a real run)</source>
        <translation>Будет выполнен &lt;b&gt;тестовый запуск&lt;/b&gt; без сохранения изменений (хотя результат выполнения будет почти таким же, как и при настоящем запуске)</translation>
    </message>
    <message>
        <location line="+14"/>
        <source>start</source>
        <translation>Начать</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>ABORT</source>
        <translation>Прервать</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>cancel</source>
        <translation>Отмена</translation>
    </message>
    <message>
        <location filename="../src/manageWizard.cpp" line="-411"/>
        <source>The restore directory will become identical to the backup snapshot</source>
        <translation>Каталог назначения станет точной копией каталога резервной копии</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Existing backup files will replace the corresponding files at the restore directory</source>
        <comment>information message - line1.</comment>
        <translation>Файлы резервной копии заменят соответствующие файлы в каталоге назначения</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>If the information above is correct, click &lt;b&gt;start&lt;/b&gt; to begin</source>
        <comment>information message - line2.
Please leave tags &lt;b&gt;&lt;/b&gt; intact and surrounding 'start translated'</comment>
        <translation>Если приведенная выше информация правильная, нажмите кнопку &lt;b&gt;Начать&lt;/b&gt;</translation>
    </message>
    <message>
        <location line="+119"/>
        <source>success</source>
        <comment>info message displayed after ...logfile deletion</comment>
        <translation>выполнено</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>failed</source>
        <comment>info message displayed after ...logfile deletion</comment>
        <translation>не выполнено</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Deleting file that lists snapshot changes</source>
        <comment>info message displayed during ...file deletion</comment>
        <translation>Удаление файла со списком изменений между резервными копиями</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>success</source>
        <comment>info message displayed after ...file deletion</comment>
        <translation>выполнено</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>failed</source>
        <comment>info message displayed after ...file deletion</comment>
        <translation>не выполнено</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>success</source>
        <comment>info message displayed after ...snapshots list update</comment>
        <translation>выполнено</translation>
    </message>
    <message>
        <location line="+73"/>
        <source>Select new restore directory</source>
        <comment>directory selection dialog title</comment>
        <translation>Выберите другой каталог назначения</translation>
    </message>
    <message>
        <location line="+81"/>
        <source>Restore path</source>
        <comment>...is the restore directory path</comment>
        <translation>Каталог назначения</translation>
    </message>
    <message>
        <location line="+124"/>
        <source>No snapshot specific data exist. Skipping...</source>
        <comment>info message displayed during ...data restoration/deletion</comment>
        <translation>Файлы резервной копии не содержат изменений. Пропуск...</translation>
    </message>
    <message>
        <location filename="../ui/manageWizard.ui" line="-150"/>
        <source>Check this, to clone the backup snapshot to the restore directory.</source>
        <translation>Установите, чтобы создать точную копию каталогов резервной копии и назначения.</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Delete existing data that do not exist at the backup</source>
        <translation>Удалить файлы в каталоге назначения, которых нет в резервной копии</translation>
    </message>
    <message>
        <location line="+37"/>
        <source>Browse locally for a new restore path</source>
        <translation>Выбрать другой каталог назначения</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>change</source>
        <translation>Изменить</translation>
    </message>
    <message>
        <location line="+14"/>
        <source>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:'FreeSans'; font-size:9pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:&apos;DejaVu Sans&apos;;&quot;&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;FreeSans&apos;; font-size:9pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:&apos;DejaVu Sans&apos;;&quot;&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
</context>
<context>
    <name>modifyDialog</name>
    <message>
        <location filename="../src/modifyDialog.cpp" line="+235"/>
        <source>simple</source>
        <translation>Простой</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>advanced</source>
        <translation>Расширенный</translation>
    </message>
    <message>
        <location line="+129"/>
        <source>Task name</source>
        <translation>Название задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Destination</source>
        <translation>Назначение</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Source</source>
        <translation>Источник</translation>
    </message>
    <message>
        <location filename="../ui/modifyDialog.ui" line="+29"/>
        <source>Task properties</source>
        <translation>Параметры задачи</translation>
    </message>
    <message>
        <location line="+54"/>
        <location line="+28"/>
        <source>Enter a name for this task (eg &quot;Backup my home directory&quot;)</source>
        <translation>Введите название задачи (например, &quot;Резервное копирование домашнего каталога&quot;)</translation>
    </message>
    <message>
        <location line="-22"/>
        <source>Name :</source>
        <translation>Название:</translation>
    </message>
    <message>
        <location line="+41"/>
        <source>Define the type of this task:
1. Backup the contents of Source inside Destination
2. Backup Source directory by name inside Destination
3. Synchronize Source &amp; Destination, keeping the most recent files at both of them</source>
        <translation>Определите тип этой задачи:
1. Архивировать содержимое Источника внутри Назначения
2. Архивировать директорию Источника по имени внутри Назначения
3. Синхронизировать Источник и Назначение, сохраняя в них самые свежие файлы</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Type :</source>
        <translation>Тип:</translation>
    </message>
    <message>
        <location line="+27"/>
        <source>Synchronize Source and Destination</source>
        <translation>Синхронизация каталогов Источника и Назначения</translation>
    </message>
    <message>
        <location line="+20"/>
        <location line="+31"/>
        <source>Enter the full path of the source directory (eg /home/luckyb/)</source>
        <translation>Введите полный путь к каталогу Источника (например, /home/luckyb/)</translation>
    </message>
    <message>
        <location line="-28"/>
        <source>Source :</source>
        <translation>Источник:</translation>
    </message>
    <message>
        <location line="+44"/>
        <location line="+73"/>
        <location line="+2724"/>
        <source>browse localy</source>
        <translation>Выбор каталога на диске</translation>
    </message>
    <message>
        <location line="-2771"/>
        <location line="+31"/>
        <source>Enter the full path of the destination directory (eg /media/backups/SiduxHome/)</source>
        <translation>Введите полный путь к каталогу Назначения (например, /media/backups/SiduxHome/)</translation>
    </message>
    <message>
        <location line="-28"/>
        <source>Destination :</source>
        <translation>Назначение:</translation>
    </message>
    <message>
        <location line="+1663"/>
        <source>eg -C4c arcfour,blowfish-cbc</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+383"/>
        <source>With this option rsync will transfer numeric group and user IDs
rather than using user and group names
and mapping them at both ends.
(--numeric-ids)</source>
        <translation>Вместо имен групп и пользователей посылаются их числовые id
и ставятся в соответствие друг другу на обоих концах.
(--numeric-ids)</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Use numeric group and user IDs</source>
        <translation>Использовать числовые ID</translation>
    </message>
    <message utf8="true">
        <location line="+22"/>
        <source>This tells the receiving side to attempt super-user activities
even if the receiving rsync wasn’t run by the super-user.
These activities include:
preserving users via the --owner option
preserving all groups (not just the current user’s groups) via the --groups option
and copying devices via the --devices option.
(--super)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+9"/>
        <source>Attempt super-user activities</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+22"/>
        <source>Try to backup open files in windows systems using vss (Only works on windows 2000 and upper)
(--vss)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+4"/>
        <source>Backup open files</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+25"/>
        <source>Restore backed-up windows permissions localized in nt-streams 
(--restore-nt-streams)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+535"/>
        <location line="+10"/>
        <source>Repeat any command that fails, x times</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="-7"/>
        <source>Repeat on fail:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+359"/>
        <source>Check this to clone source to destination
Leave unchecked to create an extra directory inside destination</source>
        <translation>Установите флажок, чтобы создавать резервные копии Источника внутри Назначения
Снимите флажок, чтобы создавать резервные копии Источника внутри вложенного каталога Назначения</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Do NOT create extra directory</source>
        <translation>НЕ создавать вложенного каталога</translation>
    </message>
    <message>
        <location line="+20"/>
        <source>Advanced</source>
        <translation>Расширенный</translation>
    </message>
    <message>
        <location line="+42"/>
        <source>Shows the rsync command as it will be executed</source>
        <translation>Показать команду rsync, которая будет выполнена</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>validate</source>
        <translation>Проверить</translation>
    </message>
    <message>
        <location line="+36"/>
        <source>Okay</source>
        <translation>OK</translation>
    </message>
    <message>
        <location line="+21"/>
        <source>Cancel</source>
        <translation>Отмена</translation>
    </message>
    <message>
        <location line="-3067"/>
        <source>Exclude</source>
        <translation>Исключить</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Add any directory, file or pattern to be excluded from this task</source>
        <translation>Добавьте любой каталог, файл или шаблон для исключения из этой задачи</translation>
    </message>
    <message>
        <location line="+18"/>
        <location line="+1612"/>
        <source>Templates</source>
        <translation>Шаблоны</translation>
    </message>
    <message>
        <location line="-1585"/>
        <source>Exclude all temp folders (**/*tmp*/)</source>
        <translation>Исключить все временные каталоги (**/*tmp*/)</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Temporary folders</source>
        <translation>Временные каталоги</translation>
    </message>
    <message>
        <location line="+31"/>
        <source>Exclude system mount folders /mnt &amp; /media (/mnt/*/**, /media/*/**)</source>
        <translation>Исключить смонтированные каталоги /mnt и /media (/mnt/*/**, /media/*/**)</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>System mount folders</source>
        <translation>Смонтированные каталоги</translation>
    </message>
    <message>
        <location line="+37"/>
        <source>Exclude all backup files &amp; folders (**~)</source>
        <translation>Исключить все архивные файлы и каталоги (**~)</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Backup files</source>
        <translation>Архивные файлы</translation>
    </message>
    <message>
        <location line="+37"/>
        <source>System folders</source>
        <translation>Системные каталоги</translation>
    </message>
    <message>
        <location line="+31"/>
        <source>Exclude all cache folders (**/*cache*/ &amp; **/*Cache*/)</source>
        <translation>Исключить все каталоги с кэшем (**/*cache*/ &amp; **/*Cache*/)</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Cache folders</source>
        <translation>Каталоги с кэшем</translation>
    </message>
    <message>
        <location line="+68"/>
        <source>Exclude all user&apos;s trash folders (**/*Trash*/, **/*trash*/)</source>
        <translation>Исключить все каталоги с корзиной (**/*Trash*/, **/*trash*/)</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Trash</source>
        <translation>Корзину</translation>
    </message>
    <message>
        <location line="-43"/>
        <source>Exclude all &quot;lost+found&quot; folders (**/lost+found*/)</source>
        <translation>Исключить все каталоги &apos;lost+found&apos; (**/lost+found*/)</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>lost+found</source>
        <translation>lost+found</translation>
    </message>
    <message>
        <location line="+106"/>
        <source>User Defined</source>
        <translation>Заданные пользователем</translation>
    </message>
    <message>
        <location line="+82"/>
        <source>Add exclusion as entered in the next field</source>
        <translation>Добавить исключение, введённое в поле</translation>
    </message>
    <message>
        <location line="+3"/>
        <location line="+371"/>
        <location line="+1337"/>
        <location line="+279"/>
        <location line="+301"/>
        <source>add</source>
        <translation>Добавить</translation>
    </message>
    <message>
        <location line="-2270"/>
        <location line="+31"/>
        <source>Exclude list</source>
        <translation>Список исключений</translation>
    </message>
    <message>
        <location line="-117"/>
        <source>Enter here file, folder or pattern and then press the &quot;add&quot; button to add it to the exclude list
* - matches any non-empty component (it stops at slashes)
** - matches anything, including slashes
? - matches any character except a slash
trailing dir_name/*** - matches both the directory &amp; everything in it
starting / - pattern is anchored to a particular spot in the hierarchy of the transfer (normaly this is the &quot;source&quot;)
trailing / - only directory is matched, not regular files, symlinks or devices</source>
        <translation>Введите здесь имя файла, каталога или шаблон, затем нажмите кнопку &quot;Добавить&quot; для добавления его в список исключений
*		- означает любой непустой символ (останавливается на слэшах)
**		- означает любой символ, включая слэш
?		- означает любой символ, кроме слэша
имя_каталога/*** (в конце)	- означает и каталог, и всё его содержимое
/ (в начале)		- шаблон привязывается к конкретному месту в иерархии каталогов (обычно это Источник)
/ (в конце)		- соответствует только каталогу, но не обычным файлам, ссылкам или устройствам</translation>
    </message>
    <message>
        <location line="-565"/>
        <source>Define the type of this task:
1. Backup the Source directory, inside Destination (see also &quot;Do NOT create directory&quot; box)
2. Synchronize Source &amp; Destination, keeping the most recent files at both of them</source>
        <translation>Определите тип этой задачи:
1. Резервная копия каталога Источника внутри Назначения (обратите внимание на флажок &quot;НЕ создавать вложенного каталога&quot;)
2. Синхронизация каталогов Источника и Назначения, сохраняются новые файлы в обоих каталогах</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Backup Source inside Destination</source>
        <translation>Резервная копия Источника внутри Назначения</translation>
    </message>
    <message>
        <location line="+174"/>
        <source>Description</source>
        <translation>Описание</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Task description</source>
        <translation>Описание задачи</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Type a description of the task</source>
        <translation>Введите описание задачи</translation>
    </message>
    <message>
        <location line="+173"/>
        <source>Exclude system folders /var, /proc, /dev &amp; /sys (/var/run/**, /run/**, /proc/**, /dev/**, /sys/**)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+148"/>
        <source>Exclude all user&apos;s .gvfs folders (**/.gvfs/)</source>
        <translation>Исключить все пользовательские каталоги .gvfs (**/.gvfs/)</translation>
    </message>
    <message>
        <location line="+77"/>
        <location line="+371"/>
        <source>launch the pattern editor</source>
        <translation>Открыть редактор шаблонов</translation>
    </message>
    <message>
        <location line="-242"/>
        <source>Remove highlighted exclusion from list</source>
        <translation>Удалить выбранный пункт из списка</translation>
    </message>
    <message>
        <location line="+3"/>
        <location line="+366"/>
        <location line="+1337"/>
        <location line="+279"/>
        <location line="+301"/>
        <source>remove</source>
        <translation>Удалить</translation>
    </message>
    <message>
        <location line="-2269"/>
        <location line="+423"/>
        <location line="+1280"/>
        <location line="+279"/>
        <location line="+301"/>
        <source>Edit highlighted inclusion</source>
        <translation>Изменить выбранный пункт</translation>
    </message>
    <message>
        <location line="-2280"/>
        <location line="+423"/>
        <location line="+1280"/>
        <location line="+279"/>
        <location line="+301"/>
        <source>edit</source>
        <translation>Изменить</translation>
    </message>
    <message>
        <location line="-2269"/>
        <location line="+423"/>
        <location line="+1280"/>
        <location line="+279"/>
        <location line="+301"/>
        <source>Move highlighted inclusion up</source>
        <translation>Переместить выбранный пункт вверх</translation>
    </message>
    <message>
        <location line="-2280"/>
        <location line="+423"/>
        <location line="+1280"/>
        <location line="+279"/>
        <location line="+301"/>
        <source>move up</source>
        <translation>Вверх</translation>
    </message>
    <message>
        <location line="-2269"/>
        <location line="+423"/>
        <location line="+1280"/>
        <location line="+279"/>
        <location line="+301"/>
        <source>Move highlighted inclusion down</source>
        <translation>Переместить выбранный пункт вниз</translation>
    </message>
    <message>
        <location line="-2280"/>
        <location line="+423"/>
        <location line="+1280"/>
        <location line="+279"/>
        <location line="+301"/>
        <source>move down</source>
        <translation>Вниз</translation>
    </message>
    <message>
        <location line="-2177"/>
        <source>Include ONLY this list of patterns. Nothing more.
Please refer to the manual for better understanding of include rules.
This will disable the exclude feature.</source>
        <translation>Включаются ТОЛЬКО файлы, указанные в списке включений, больше ничего.
Подробнее смотрите в руководстве пользователя.
Правила, определённые в списке исключений, не применяются.</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>Only Include</source>
        <translation>Включать только перечисленное</translation>
    </message>
    <message>
        <location line="+55"/>
        <source>Enter here file, folder or pattern and then press the &quot;add&quot; button to add it to the include list
* - matches any non-empty component (it stops at slashes)
** - matches anything, including slashes
? - matches any character except a slash
trailing dir_name/*** - matches both the directory &amp; everything in it
starting / - pattern is anchored to a particular spot in the hierarchy of the transfer (normaly this is the &quot;source&quot;)
trailing / - only directory is matched, not regular files, symlinks or devices</source>
        <translation>Введите здесь имя файла, каталога или шаблон, затем нажмите кнопку &quot;Добавить&quot; для добавления его в список исключений
*		- означает любой непустой символ (останавливается на слэшах)
**		- означает любой символ, включая слэш
?		- означает любой символ, кроме слэша
имя_каталога/*** (в конце)	- означает и каталог, и всё его содержимое
/ (в начале)		- шаблон привязывается к конкретному месту в иерархии каталогов (обычно это Источник)
/ (в конце)		- соответствует только каталогу, но не обычным файлам, ссылкам или устройствам</translation>
    </message>
    <message>
        <location line="+65"/>
        <source>Add inclusion as entered in the next field</source>
        <translation>Добавить включение, введённое в поле</translation>
    </message>
    <message>
        <location line="+19"/>
        <location line="+28"/>
        <source>Include list</source>
        <translation>Список включений</translation>
    </message>
    <message>
        <location line="+34"/>
        <source>Remove highlighted inclusion from list</source>
        <translation>Удалить выбранный пункт из списка</translation>
    </message>
    <message>
        <location line="+123"/>
        <source>Remote</source>
        <translation>Удалённое подключение</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Use a remote host either for source or destination</source>
        <translation>Использовать удалённый хост в качестве Источника или Назначения</translation>
    </message>
    <message>
        <location line="+12"/>
        <source>Use remote host</source>
        <translation>Использовать удалённое подключение</translation>
    </message>
    <message>
        <location line="+27"/>
        <source>Use a remote host for destination data.</source>
        <translation>Использовать удалённый хост в качестве Назначения.</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>destination</source>
        <translation>Назначение</translation>
    </message>
    <message>
        <location line="+25"/>
        <source>Use a remote host for source data.</source>
        <translation>Использовать удалённый хост в качестве Источника.</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>source</source>
        <translation>Источник</translation>
    </message>
    <message>
        <location line="+27"/>
        <source>User:</source>
        <translation>Пользователь:</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>Enter your username for the remote host (leave blank if not applicable).</source>
        <translation>Введите имя пользователя для удалённого хоста (оставьте пустым, если не требуется).</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>@Host:</source>
        <translation>@Хост:</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>Enter the name of the remote host.</source>
        <translation>Введите название удалённого хоста.</translation>
    </message>
    <message>
        <location line="+33"/>
        <source>Enter the full path of the file that contains the rsync (not the ssh) authentication password (leave blank if not applicable).</source>
        <translation>Введите полный путь к файлу, содержащему аутентификационный пароль для rsync (не ssh) (оставьте пустым, если не используется)</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>rsync password file:</source>
        <translation>Файл пароля rsync:</translation>
    </message>
    <message>
        <location line="+22"/>
        <source>Check this to connect to an rsync Remote module</source>
        <translation>Отметьте это для соединения с Удаленным модулем rsync</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Remote module</source>
        <translation>Удаленный модуль</translation>
    </message>
    <message>
        <location line="+74"/>
        <source>Use ssh as transport shell</source>
        <translation>Использовать ssh как транспорт</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>ssh</source>
        <translation>ssh</translation>
    </message>
    <message>
        <location line="+75"/>
        <source>password:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+91"/>
        <source>Enter the full path of the file that contains the private ssh authentication key (leave blank if not applicable).

Note that you have to do all actions needed for a passwordless ssh remote connection using an OpenSSH key pair</source>
        <translation>Введите полный путь к файлу, который содержит приватный аутентификационный ключ ssh (оставьте пустым, если не используется).

Проверьте, сделали ли Вы все действия, необходимые для беспарольного ssh-соединения с использованием пары ключей OpenSSH</translation>
    </message>
    <message>
        <location line="-31"/>
        <source>private key file :</source>
        <translation>Файл с приватным ключем:</translation>
    </message>
    <message>
        <location line="-88"/>
        <source>Enter the port you would like to use for the ssh connection (leave blank for default port)</source>
        <translation>Введите порт, который вы хотите использовать для ssh-соединения (оставьте пустым для значения по-умолчанию)</translation>
    </message>
    <message>
        <location line="-25"/>
        <source>port :</source>
        <translation>Порт:</translation>
    </message>
    <message>
        <location line="+267"/>
        <source>Command Options</source>
        <translation>Опции</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Add or remove any rsync options.
If you have no idea what these mean, leave them untouched !!</source>
        <translation>Добавить или удалить опции rsync.
Если Вы не совсем понимаете, что это такое - не трогайте их!!</translation>
    </message>
    <message>
        <location line="+84"/>
        <source>Delete files on the destination that don't exist on the source
. &quot;Recurse into directories&quot; has to be selected 
(--delete-after &amp; --delete-excluded if &quot;Exclude&quot; is used)</source>
        <translation>Удалять файлы в каталоге Назначения, которых нет в Источнике.
Также должно быть выбрано &quot;Рекурсивно в подкаталогах&quot;
(--delete-after и --delete-excluded если используется &quot;Исключить&quot;)</translation>
    </message>
    <message>
        <location line="+152"/>
        <source>Copy device (super user only)  &amp; special files as they are
(-D)</source>
        <translation>Копировать файлы физических устройств (только для суперпользователя), именованные каналы (буферы FIFO), гнёзда (сокеты)
(-D)</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Preserve device, special files</source>
        <translation>Сохранять файлы устройств,
специальные файлы</translation>
    </message>
    <message>
        <location line="+51"/>
        <source>Files that are hard-linked together on the source will hard-link together on the destination
WARNING: All files have to be included in the transfer set !!
(-H)</source>
        <translation>Указывает пересоздать жесткие ссылки в Назначении в соответствии с тем, что имеется в Источнике.
Без этого параметра жесткие ссылки обрабатываются как обычные файлы.
ВНИМАНИЕ: rsync может обнаруживать жесткие ссылки, только если обе части ссылки
попадают в список предназначенных к передаче файлов!!
(-H)</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>Preserve hard links</source>
        <translation>Сохранять жесткие ссылки</translation>
    </message>
    <message>
        <location line="-207"/>
        <source>Delete files on the destination</source>
        <translation>Удалять отсутствующие файлы</translation>
    </message>
    <message>
        <location line="+54"/>
        <source>Recurse into directories 
(-r)</source>
        <translation>Указывает rsync копировать каталоги рекурсивно
(-r)</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Recurse into directories</source>
        <translation>Рекурсивно в подкаталогах</translation>
    </message>
    <message>
        <location line="+54"/>
        <source>Do not backup source files that are newer on the destination 
(--update)</source>
        <translation>Пропускать любые файлы, уже существующие в Назначении с более поздней датой, чем в Источнике
(--update)</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Skip newer destination files</source>
        <translation>Пропускать новые файлы</translation>
    </message>
    <message>
        <location line="-156"/>
        <source>Preserve the owner (super user only), group &amp; time stamp of files
(-tgo)</source>
        <translation>Сохранять атибуты владельца (только для суперпользователя) и группы, время модификации файлов
(-tgo)</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Preserve ownership, times</source>
        <translation>Сохранять владельца и даты</translation>
    </message>
    <message>
        <location line="+61"/>
        <source>Preserve permissions of files
(-p)</source>
        <translation>Копирует все права на приёмную сторону точь в точь с оригиналом
(-p)</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Preserve permissions</source>
        <translation>Сохранять права</translation>
    </message>
    <message>
        <location line="+54"/>
        <source>Copy symlinks as symlinks
(-l)</source>
        <translation>Если обнаружена символьная ссылка, то она же создается и на приёмной стороне
(-l)</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Preserve symlinks</source>
        <translation>Сохранять символические ссылки</translation>
    </message>
    <message>
        <location line="+89"/>
        <source>Ignore files using a similar algorithm to CVS 
(-C)</source>
        <translation>Игнорировать файлы, используя похожий на CVS алгоритм
(-C)</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Ignore files the CVS way</source>
        <translation>Игнорировать файлы как CVS</translation>
    </message>
    <message>
        <location line="+197"/>
        <source>User defined</source>
        <translation>Заданные пользователем</translation>
    </message>
    <message>
        <location line="+30"/>
        <source>Enter here an rsync option to add (eg &quot;--delete-excluded&quot;, &quot;-X&quot;)</source>
        <translation>Введите сюда дополнительные опции rsync (например, &quot;--delete-excluded&quot;, &quot;-X&quot;)</translation>
    </message>
    <message>
        <location line="+81"/>
        <source>Extra rsync options list</source>
        <translation>Список дополнительных опций rsync</translation>
    </message>
    <message>
        <location line="+34"/>
        <source>Remove highlighted option from list</source>
        <translation>Удалить выбранный пункт из списка</translation>
    </message>
    <message>
        <location line="-81"/>
        <source>Add rsync option as entered in the next field</source>
        <translation>Добавить опцию rsync, введённую в поле</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>options list</source>
        <translation>Список опций</translation>
    </message>
    <message>
        <location line="+145"/>
        <source>Also Execute</source>
        <translation>Также выполнить</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Execute extra commands, before or after the task.</source>
        <translation>Выполнить дополнительные команды до и после задачи.</translation>
    </message>
    <message>
        <location line="+18"/>
        <source>Before</source>
        <translation>До</translation>
    </message>
    <message>
        <location line="+35"/>
        <source>Enter here a command to be executed before the task and then press the &quot;add&quot; button to add it to the list below</source>
        <translation>Введите команду, которая должна выполняться перед задачей и затем нажмите кнопку &quot;Добавить&quot; для добавления в список ниже</translation>
    </message>
    <message>
        <location line="+59"/>
        <location line="+301"/>
        <source>Add command as entered in the field beside</source>
        <translation>Добавить команду, введенную в поле рядом</translation>
    </message>
    <message>
        <location line="-254"/>
        <location line="+301"/>
        <source>Command list</source>
        <translation>Список команд</translation>
    </message>
    <message>
        <location line="-267"/>
        <location line="+301"/>
        <source>Remove highlighted command from list</source>
        <translation>Удалить выбранный пункт из списка</translation>
    </message>
    <message>
        <location line="-197"/>
        <source>Execute the task even if it appears with a WARNING message
Normally used when &quot;Execute Before&quot; commands can fix a warning (eg mount partitions)

ATTENTION: check this if you really know what you&apos;re doing</source>
        <translation>Выполнить задачу, даже если появляется ПРЕДУПРЕЖДЕНИЕ
Обычно используется, когда команды, выполняющиеся до запуска задачи,
могут устранить причину предупреждения (например, примонтировать раздел)

ВНИМАНИЕ: используйте, только если вы точно знаете, что делаете</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>by-pass WARNING</source>
        <translation>отключить
ПРЕДУПРЕЖДЕНИЯ</translation>
    </message>
    <message>
        <location line="+16"/>
        <source>After</source>
        <translation>После</translation>
    </message>
    <message>
        <location line="+35"/>
        <source>Enter here a command to be executed after the task and then press the &quot;add&quot; button to add it to the list below</source>
        <translation>Введите команду, которая должна выполняться после задачи и затем нажмите кнопку &quot;Добавить&quot; для добавления в список ниже</translation>
    </message>
    <message>
        <location filename="../src/modifyDialog.cpp" line="-106"/>
        <source>Select source directory</source>
        <comment>file selection dialog title</comment>
        <translation>Выберите каталог Источника</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Select destination directory</source>
        <comment>file selection dialog title</comment>
        <translation>Выберите каталог Назначения</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Select rsync password file</source>
        <comment>file selection dialog title</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+7"/>
        <location line="+2"/>
        <source>Select ssh keyfile</source>
        <comment>file selection dialog title</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+5"/>
        <location line="+6"/>
        <source>Select command to be executed</source>
        <comment>file selection dialog title</comment>
        <translation>Выберите выполняемую команду</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Select file to read include patterns</source>
        <comment>file selection dialog title</comment>
        <translation>Выберите файл для загрузки шаблонов включения</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Select file to read exclude patterns</source>
        <comment>file selection dialog title</comment>
        <translation>Выберите файл для загрузки шаблонов исключения</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>Please define the source before launching the pattern editor</source>
        <comment>message box, message</comment>
        <translation>Перед запуском редактора шаблонов выберите каталог Источника</translation>
    </message>
    <message>
        <location line="+40"/>
        <source>ERROR</source>
        <comment>message box message</comment>
        <translation>ОШИБКА</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Please specify the following before proceeding:</source>
        <comment>message box, message</comment>
        <translation>Перед продолжением задайте следующие параметры:</translation>
    </message>
    <message>
        <location line="+14"/>
        <location line="+10"/>
        <location line="+13"/>
        <location line="+18"/>
        <location line="+18"/>
        <location line="+9"/>
        <source>ERROR</source>
        <comment>message box message - line1</comment>
        <translation>ОШИБКА</translation>
    </message>
    <message>
        <location line="-66"/>
        <source>That is not allowed because &apos;/&apos; does not have an actual name</source>
        <comment>message box message - line2</comment>
        <translation>Это неправильно, поскольку &apos;/&apos; недопустимое имя каталога</translation>
    </message>
    <message>
        <location line="-334"/>
        <source>Leave the box checked, to &lt;b&gt;STOP&lt;/b&gt; the execution of running task if this command exits with an error</source>
        <translation>Установленный флажок означает, что выполнение задачи &lt;b&gt;ОСТАНОВИТСЯ&lt;/b&gt; при выполнении команды с ошибкой</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>use boxes to &lt;b&gt;STOP&lt;/b&gt; task execution on error</source>
        <comment>Please leave the bold tags &lt;b&gt;&lt;/b&gt; intact and surrounding the word STOP translated</comment>
        <translation>Флажок - &lt;b&gt;ОСТАНОВИТЬ&lt;/b&gt; задачу при ошибках</translation>
    </message>
    <message>
        <location line="+332"/>
        <source>You have declared the &apos;/&apos; (root) directory as source and have NOT checked the &apos;Do NOT create extra directory&apos; box</source>
        <comment>message box message - line1</comment>
        <translation>Вы определили &apos;/&apos; (корневой каталог) как Источник и НЕ установили флажок &quot;НЕ создавать вложенного каталога&quot;</translation>
    </message>
    <message>
        <location line="+2"/>
        <location line="+10"/>
        <source>Please check the relevant box before proceeding</source>
        <comment>message box message - line3</comment>
        <translation>Перед продолжением установите соответствующий флажок</translation>
    </message>
    <message>
        <location line="-2"/>
        <source>You have declared the root directory of an entire partition as source and have NOT checked the &apos;Do NOT create extra directory&apos; box</source>
        <comment>message box message - line1</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>That is not allowed because the root partition does not have an actual name</source>
        <comment>message box message - line2</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+12"/>
        <source>The name of the task you requested already exists</source>
        <comment>message box message - line1</comment>
        <translation>Введённое название задачи уже существует</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Please specify a different name before proceeding</source>
        <comment>message box message - line2</comment>
        <translation>Перед продолжением задайте другое название</translation>
    </message>
    <message>
        <location line="+17"/>
        <source>The source you have declared is identical to the destination</source>
        <comment>message box message - line1</comment>
        <translation>Каталог Назначение совпадает с каталогом Источник</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Please modify at least one of them</source>
        <comment>message box message - line2</comment>
        <translation>Измените хотя бы один из них</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>WARNING</source>
        <comment>message box message - line1</comment>
        <translation>ПРЕДУПРЕЖДЕНИЕ</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>You have declared a destination that is part of the source directory structure</source>
        <comment>message box message - line1</comment>
        <translation>Вы определили каталог Назначение как часть структуры каталогов Источника</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>&lt;b&gt;Do not forget&lt;/b&gt; to define a directory at the &apos;exclude&apos; groupbox that will contain the destination</source>
        <comment>message box message - line2. Please leave tag &lt;b&gt;,&lt;/b&gt; intact and surrounding 'do not forget' translated</comment>
        <translation>&lt;b&gt;Не забудьте&lt;/b&gt; добавить каталог Назначение в список на вкладке &quot;Исключить&quot;</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>You have checked the &apos;delete files on the destination&apos; option</source>
        <comment>message box message - line2</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>without having checked &apos;Recurse into directories&apos; which is required</source>
        <comment>message box message - line3</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+8"/>
        <source>&apos;Remote Host&apos; is checked, but no remote host name is declared</source>
        <comment>message box message - line2</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>Please specify a remote host name</source>
        <comment>message box message - line3</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>Otherwise uncheck &apos;Remote Host&apos; to operate locally</source>
        <comment>message box message - line4</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+64"/>
        <source>All declared fields of the task properties window seem to be ok</source>
        <comment>message box message first line</comment>
        <translation>Похоже, что все поля в окне заполнены правильно</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Errors have been found</source>
        <comment>message box message first line</comment>
        <translation>Были обнаружены ошибки</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>command to be executed</source>
        <comment>full phrase: command to be executed: &lt;COMMAND&gt;</comment>
        <translation>команда на выполнение</translation>
    </message>
    <message>
        <location line="+40"/>
        <source>You have already added this exclude item</source>
        <comment>message box message</comment>
        <translation>Вы уже добавили это исключение</translation>
    </message>
    <message>
        <location line="+55"/>
        <source>You have already added this include item</source>
        <comment>message box message</comment>
        <translation>Вы уже добавили это включение</translation>
    </message>
    <message>
        <location line="+53"/>
        <source>You have already added this option</source>
        <comment>message box message</comment>
        <translation>Вы уже добавили эту опцию</translation>
    </message>
    <message>
        <location line="+266"/>
        <location line="+25"/>
        <location line="+25"/>
        <location line="+25"/>
        <location line="+26"/>
        <source>done</source>
        <translation>OK</translation>
    </message>
    <message>
        <location line="-100"/>
        <location line="+25"/>
        <location line="+25"/>
        <location line="+25"/>
        <location line="+26"/>
        <source>done editing</source>
        <translation>Сохранить изменения</translation>
    </message>
    <message>
        <location line="-99"/>
        <location line="+25"/>
        <location line="+25"/>
        <location line="+25"/>
        <location line="+26"/>
        <source>cancel</source>
        <translation>Отмена</translation>
    </message>
    <message>
        <location line="-100"/>
        <location line="+25"/>
        <location line="+25"/>
        <location line="+25"/>
        <location line="+26"/>
        <source>cancel editing</source>
        <translation>Отменить изменения</translation>
    </message>
    <message>
        <location filename="../ui/modifyDialog.ui" line="-2060"/>
        <source>Read exclude patterns from file</source>
        <translation>Загрузить из файла шаблоны исключения</translation>
    </message>
    <message>
        <location line="+3"/>
        <location line="+315"/>
        <source>Read file:</source>
        <translation>Открыть файл:</translation>
    </message>
    <message>
        <location line="-305"/>
        <location line="+315"/>
        <source>filename</source>
        <translation>Имя файла</translation>
    </message>
    <message>
        <location line="-305"/>
        <location line="+315"/>
        <source>browse</source>
        <translation>Выбор файла</translation>
    </message>
    <message>
        <location line="-312"/>
        <location line="+315"/>
        <source>...</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="-297"/>
        <source>Include</source>
        <translation>Включить</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Add any directory, file or pattern to be included by this task</source>
        <translation>Добавьте любой каталог, файл или шаблон для включения в эту задачу</translation>
    </message>
    <message>
        <location line="+20"/>
        <source>Include mode</source>
        <translation>Метод обработки списка включений</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Mode:</source>
        <translation>Метод:</translation>
    </message>
    <message>
        <location line="+22"/>
        <source>Do not exclude this list of patterns.
Please refer to the manual for better understanding of include rules.</source>
        <translation>Файлы, которые должны исключаться согласно списку исключений, включаются согласно списку включений.
Подробнее смотрите в руководстве пользователя.</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Normal Include</source>
        <translation>Не исключать перечисленное</translation>
    </message>
    <message>
        <location line="+219"/>
        <source>Read include patterns from file</source>
        <translation>Загрузить из файла шаблоны включения</translation>
    </message>
    <message>
        <location line="+344"/>
        <location line="+248"/>
        <location line="+868"/>
        <source>browse locally</source>
        <translation>Выбор файла на диске</translation>
    </message>
    <message>
        <location line="-835"/>
        <source>additional options:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+387"/>
        <source>Check this is you use a FAT/NTFS partition as destination.
Data ownership and permissions will NOT be preserved.
(-t --modify-window=1)</source>
        <translation>Установите, если каталог Назначения находится на разделе FAT/NTFS.
Права доступа не будут сохраняться.
(-t --modify-window=1)</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>Destination is FAT/NTFS</source>
        <translation>Назначение - раздел FAT/NTFS</translation>
    </message>
    <message>
        <location line="+114"/>
        <source>Restore permissions</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+855"/>
        <location line="+22"/>
        <source>Set the total number of backup snapshots to keep</source>
        <translation>Количество сохраняемых резервных копий</translation>
    </message>
    <message>
        <location line="-19"/>
        <source>Snapshots to keep:</source>
        <translation>Резервных копий:</translation>
    </message>
</context>
<context>
    <name>patternEditor</name>
    <message>
        <location filename="../src/patternEditor.cpp" line="+44"/>
        <location line="+89"/>
        <location line="+155"/>
        <source>directory :</source>
        <translation>Каталог:</translation>
    </message>
    <message>
        <location line="-145"/>
        <source>Select file</source>
        <translation>Укажите файл</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Please choose a file within the source</source>
        <translation>Выберите файл внутри источника</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Select directory</source>
        <translation>Укажите каталог</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>Please choose a directory within the source</source>
        <translation>Выберите каталог внутри источника</translation>
    </message>
    <message>
        <location line="+105"/>
        <source>file :</source>
        <translation>Файл:</translation>
    </message>
    <message>
        <location filename="../ui/patternEditor.ui" line="+23"/>
        <source>pattern editor</source>
        <translation>Редактор шаблонов</translation>
    </message>
    <message>
        <location line="+100"/>
        <source>Check this to use the directory above as an absolute path
if unchecked, the pattern will match any file/directory that meets the &quot;name&quot; criteria</source>
        <translation>Отметьте, чтобы использовать указанный каталог как корневой
если не отмечено, шаблон будет применяться ко всем файлам/каталогам, соответствующим критериям</translation>
    </message>
    <message>
        <location line="+171"/>
        <source>Define here, what would you like the pattern to refer to</source>
        <translation>Укажите, что нужно включить в шаблон</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>The pattern refers to a:</source>
        <translation>Что включается в шаблон:</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Use this if the pattern refers to a specific file
eg &quot;/media/music/album/song.mp3&quot;</source>
        <translation>Включить в шаблон конкретный файл
например, &quot;/media/Музыка/Альбом/Трек.mp3&quot;</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Specific file</source>
        <translation>Конкретный файл</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Use this if the pattern refers to a specific directory
eg &quot;/media/music/Album/&quot;</source>
        <translation>Включить в шаблон конкретный каталог
например, &quot;/media/Музыка/Альбом/&quot;</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Specific directory</source>
        <translation>Конкретный каталог</translation>
    </message>
    <message>
        <location line="+13"/>
        <source>Use this if the pattern refers to a set of files that have something in common
eg all the files with a &quot;.txt&quot; extension</source>
        <translation>Включить в шаблон набор файлов, названия которых имеют что-то общее
например, все файлы с расширением &quot;.txt&quot;</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Set of files</source>
        <translation>Набор файлов</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Use this if the pattern refers to a set of directories that have something in common
eg all the directories that are named as &quot;temp&quot;</source>
        <translation>Включить в шаблон набор каталогов, названия которых имеют что-то общее
например, все каталоги с названием &quot;temp&quot;</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Set of directories</source>
        <translation>Набор каталогов</translation>
    </message>
    <message>
        <location line="+50"/>
        <source>name</source>
        <translation>Названия файлов/каталогов</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>starts with :</source>
        <translation>начинаются с :</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Enter here the starting characters of the name of the files/directories that the pattern refers to</source>
        <translation>Введите начальные символы названий файлов/каталогов для включения в шаблон</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>ends with :</source>
        <translation>заканчиваются на :</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Enter here the ending characters of the name of the files/directories that the pattern refers to
eg to refer to all &quot;.txt&quot; files, enter
.txt</source>
        <translation>Введите последние символы названий файлов/каталогов для включения в шаблон
например, для включения всех файлов&quot;.txt&quot;, введите
.txt</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Enter here the name of the files/directories that the pattern refers to</source>
        <translation>Введите название файлов/каталогов для включения в шаблон</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>is exactly :</source>
        <translation>совпадают с :</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Enter here the characters contained in any position of the name of the files/directories that the pattern refers to</source>
        <translation>Введите символы, которые могут находится в любом месте названий файлов/каталогов для включения в шаблон</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>contains :</source>
        <translation>содержат :</translation>
    </message>
    <message>
        <location line="-392"/>
        <source>browse localy for a file</source>
        <translation>Выбор файла на диске</translation>
    </message>
    <message>
        <location line="+23"/>
        <source>browse localy for a directory path</source>
        <translation>Выбор каталога на диске</translation>
    </message>
    <message>
        <location line="+28"/>
        <source>use absolute path</source>
        <translation>использовать корневой каталог</translation>
    </message>
    <message>
        <location line="+35"/>
        <source>Go deeper in path by :</source>
        <translation>Глубина вложения :</translation>
    </message>
    <message>
        <location line="+36"/>
        <source>Go deeper in path by any level</source>
        <translation>Неограниченная глубина вложения подкаталогов</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>any</source>
        <translation>любая</translation>
    </message>
    <message>
        <location line="+198"/>
        <source>Define here the name criteria for the files/directories to be matched</source>
        <translation>Определите критерии совпадения для набора файлов/каталогов</translation>
    </message>
    <message>
        <location line="+88"/>
        <source>final pattern</source>
        <translation>Итоговый шаблон</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>The actual pattern is displayed here</source>
        <translation>Здесь отображается итоговый шаблон</translation>
    </message>
    <message>
        <location line="-288"/>
        <source>Reset the pattern editor fields to the default values</source>
        <translation>Вернуть все поля редактора к значениям по-умолчанию</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>reset</source>
        <translation>Сброс</translation>
    </message>
    <message>
        <location line="+33"/>
        <source>Okay</source>
        <translation>OK</translation>
    </message>
    <message>
        <location line="+21"/>
        <source>Cancel</source>
        <translation>Отмена</translation>
    </message>
    <message>
        <location line="-122"/>
        <location line="+29"/>
        <source>Use this to refer to deeper sub-directories
eg
The directory &quot;/media/music&quot; includes 3 sub-directories:
1.Rock
2.Jazz
3.Soundtracks
 and you would like to refer to all the contents of these 3, define the following:
* Set of directories
* Directory contents
* path:/media/music/
* Go deeper in path by &quot;1&quot;</source>
        <translation>Укажите глубину вложения подкаталогов
например
В каталоге &quot;/media/Музыка&quot; находятся 3 подкаталога:
1.Рок
2.Джаз
3.Саундтреки
Чтобы включить все содержимое этих 3 подкаталогов, укажите следующее:
* Набор каталогов
* Содержимое каталога
* путь :/media/Музыка/
* Глубина вложения подкаталогов &quot;1&quot;</translation>
    </message>
    <message>
        <location line="+207"/>
        <source>Use this if the pattern refers to the contents of a directory (or a set of directories), not the directory itself
eg the contents of the directory &quot;/media/music/Album/&quot;</source>
        <translation>Включить в шаблон содержимое каталога (или набора каталогов), а не сам каталог
например, содержимое каталога &quot;/media/Музыка/Альбом/&quot;</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Directory contents</source>
        <translation>Содержимое каталога</translation>
    </message>
</context>
<context>
    <name>scheduleDialog</name>
    <message>
        <location filename="../src/scheduleDialog.cpp" line="+137"/>
        <location line="+78"/>
        <source>Starting from scratch</source>
        <translation>Создан пустой файл расписания</translation>
    </message>
    <message>
        <location line="+53"/>
        <location line="+139"/>
        <location line="+45"/>
        <source>No schedules are declared !!</source>
        <translation>Не определено ни одного расписания!!</translation>
    </message>
    <message>
        <location line="-133"/>
        <source>Unable to create schedule file</source>
        <translation>Невозможно создать файл расписания</translation>
    </message>
    <message>
        <location line="+30"/>
        <source>You have reached the maximum limit of supported scheduled profiles</source>
        <translation>Достигнуто максимальное количество записей в расписании</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>You have to remove an item if you wish to add another</source>
        <translation>Удалите какой-либо элемент, чтобы добавить новую запись</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Add profile schedule</source>
        <translation>Добавить запись в расписание</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>Modify profile schedule</source>
        <translation>Изменить запись в расписании</translation>
    </message>
    <message>
        <location filename="../ui/scheduleDialog.ui" line="+182"/>
        <location filename="../src/scheduleDialog.cpp" line="+62"/>
        <source>Profile schedule details</source>
        <translation>Подробности записи в расписании</translation>
    </message>
    <message>
        <location filename="../src/scheduleDialog.cpp" line="+78"/>
        <source>Invalid profile</source>
        <translation>Неправильный профиль</translation>
    </message>
    <message>
        <location line="+67"/>
        <source>Execute profile</source>
        <translation>Выполнить профиль</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>hourly at minute </source>
        <comment>full phrase: Execute profile &lt;PROFILENAME&gt; hourly at minute &lt;MM&gt;</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+4"/>
        <source>at</source>
        <translation>в</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>every</source>
        <translation>каждый</translation>
    </message>
    <message>
        <location line="+3"/>
        <location line="+38"/>
        <source>day</source>
        <translation>день</translation>
    </message>
    <message>
        <location filename="../ui/scheduleDialog.ui" line="+251"/>
        <location filename="../src/scheduleDialog.cpp" line="-36"/>
        <source>Sunday</source>
        <translation>Воскресенье</translation>
    </message>
    <message>
        <location line="+5"/>
        <location filename="../src/scheduleDialog.cpp" line="+2"/>
        <source>Monday</source>
        <translation>Понедельник</translation>
    </message>
    <message>
        <location line="+5"/>
        <location filename="../src/scheduleDialog.cpp" line="+2"/>
        <source>Tuesday</source>
        <translation>Вторник</translation>
    </message>
    <message>
        <location line="+5"/>
        <location filename="../src/scheduleDialog.cpp" line="+2"/>
        <source>Wednesday</source>
        <translation>Среда</translation>
    </message>
    <message>
        <location line="+5"/>
        <location filename="../src/scheduleDialog.cpp" line="+2"/>
        <source>Thursday</source>
        <translation>Четверг</translation>
    </message>
    <message>
        <location line="+5"/>
        <location filename="../src/scheduleDialog.cpp" line="+2"/>
        <source>Friday</source>
        <translation>Пятница</translation>
    </message>
    <message>
        <location line="+5"/>
        <location filename="../src/scheduleDialog.cpp" line="+2"/>
        <source>Saturday</source>
        <translation>Вторник</translation>
    </message>
    <message>
        <location filename="../src/scheduleDialog.cpp" line="+5"/>
        <source>&amp; on the</source>
        <translation>и</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>st</source>
        <comment>as in 1st day</comment>
        <translation>-ый</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>nd</source>
        <comment>as in 2nd day</comment>
        <translation>-ой</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>rd</source>
        <comment>as in 3rd day</comment>
        <translation>-ий</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>th</source>
        <comment>as in 4th, 5th, 6th or 7th day</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>th</source>
        <comment>as in 8th day</comment>
        <translation>-ой</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>th</source>
        <comment>as in 9th day</comment>
        <translation>-ый</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>th</source>
        <comment>as in 10th day</comment>
        <translation>-ый</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>th</source>
        <comment>as in 11th day</comment>
        <translation>-ый</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>th</source>
        <comment>as in 12th....19th day</comment>
        <translation>-ый</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>th</source>
        <comment>as in 20th day</comment>
        <translation>-ый</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>st</source>
        <comment>as in 21st day</comment>
        <translation>-ый</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>nd</source>
        <comment>as in 22nd day</comment>
        <translation>-ой</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>rd</source>
        <comment>as in 23rd day</comment>
        <translation>-ий</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>th</source>
        <comment>as in 24th...30th day</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+1"/>
        <source>st</source>
        <comment>as in 31st day</comment>
        <translation>-ый</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>of any month</source>
        <translation>любого месяца</translation>
    </message>
    <message>
        <location line="+4"/>
        <location line="+2"/>
        <location line="+2"/>
        <location line="+2"/>
        <location line="+2"/>
        <location line="+2"/>
        <location line="+2"/>
        <location line="+2"/>
        <location line="+2"/>
        <location line="+2"/>
        <location line="+2"/>
        <location line="+2"/>
        <source>of</source>
        <translation> </translation>
    </message>
    <message>
        <location line="-22"/>
        <source>January</source>
        <comment>full phrase: 'of January'</comment>
        <translation>января</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>February</source>
        <comment>full phrase: 'of February'</comment>
        <translation>февраля</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>March</source>
        <comment>full phrase: 'of March'</comment>
        <translation>марта</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>April</source>
        <comment>full phrase: 'of April'</comment>
        <translation>апреля</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>May</source>
        <comment>full phrase: 'of May'</comment>
        <translation>мая</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>June</source>
        <comment>full phrase: 'of June'</comment>
        <translation>июня</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>July</source>
        <comment>full phrase: 'of July'</comment>
        <translation>июля</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>August</source>
        <comment>full phrase: 'of August'</comment>
        <translation>августа</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>September</source>
        <comment>full phrase: 'of September'</comment>
        <translation>сентября</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>October</source>
        <comment>full phrase: 'of October'</comment>
        <translation>октября</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>November</source>
        <comment>full phrase: 'of November'</comment>
        <translation>ноября</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>December</source>
        <comment>full phrase: 'of December'</comment>
        <translation>декабря</translation>
    </message>
    <message>
        <location line="+90"/>
        <location line="+26"/>
        <source>Unable to create cron file</source>
        <translation>Невозможно создать cron-файл</translation>
    </message>
    <message>
        <location filename="../ui/scheduleDialog.ui" line="-446"/>
        <source>luckyBackup - schedule</source>
        <translation>luckyBackup - расписание</translation>
    </message>
    <message>
        <location line="+45"/>
        <source>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:'DejaVu Sans'; font-size:10pt; font-weight:600; font-style:normal;&quot;&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;&quot;&gt;&lt;span style=&quot; font-size:9pt; color:#aa0000;&quot;&gt;Profile execution scheduling&lt;/span&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;DejaVu Sans&apos;; font-size:10pt; font-weight:600; font-style:normal;&quot;&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;&quot;&gt;&lt;span style=&quot; font-size:9pt; color:#aa0000;&quot;&gt;Расписание выполнения профиля&lt;/span&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location line="+43"/>
        <source>Add a new profile schedule</source>
        <translation>Добавить новое расписание профиля</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>add</source>
        <translation>Добавить</translation>
    </message>
    <message>
        <location line="+17"/>
        <source>Modify selected profile schedule</source>
        <translation>Изменить выбранное расписание профиля</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>modify</source>
        <translation>Изменить</translation>
    </message>
    <message>
        <location line="+14"/>
        <source>Remove selected profile schedule</source>
        <translation>Удалить выбранное расписание профиля</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>remove</source>
        <translation>Удалить</translation>
    </message>
    <message>
        <location line="+57"/>
        <source>Profile :</source>
        <translation>Профиль:</translation>
    </message>
    <message>
        <location line="+25"/>
        <source>Skip tasks that apear with a &apos;CRITICAL&apos; warning message after the directories check</source>
        <translation>Пропустить задачи, которые имеют предупреждение &quot;КРИТИЧНО&quot; после проверки каталогов</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>skip critical</source>
        <translation>Пропустить критические</translation>
    </message>
    <message>
        <location line="+29"/>
        <source>time (hour:min) :</source>
        <translation>Время (часы:минуты):</translation>
    </message>
    <message>
        <location line="+27"/>
        <source>set this value to -1 for the schedule to occur every hour</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+19"/>
        <source>:</source>
        <translation>:</translation>
    </message>
    <message>
        <location line="+71"/>
        <source>:delay</source>
        <translation>:задержка</translation>
    </message>
    <message>
        <location line="+13"/>
        <source>Delay luckybackup execution at startup</source>
        <translation>Задержка выполнения luckybackup после загрузки</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>min</source>
        <extracomment>means: minutes (time)</extracomment>
        <translation>мин</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>day of week :</source>
        <translation>День недели:</translation>
    </message>
    <message>
        <location line="+20"/>
        <location line="+63"/>
        <location line="+88"/>
        <source>Any</source>
        <translation>Любой</translation>
    </message>
    <message>
        <location line="-108"/>
        <source>month :</source>
        <translation>Месяц:</translation>
    </message>
    <message>
        <location line="+25"/>
        <source>January</source>
        <translation>Январь</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>February</source>
        <translation>Февраль</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>March</source>
        <translation>Март</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>April</source>
        <translation>Апрель</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>May</source>
        <translation>Май</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>June</source>
        <translation>Июнь</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>July</source>
        <translation>Июль</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>August</source>
        <translation>Август</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>September</source>
        <translation>Сентябрь</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>October</source>
        <translation>Октябрь</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>November</source>
        <translation>Ноябрь</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>December</source>
        <translation>Декабрь</translation>
    </message>
    <message>
        <location line="+8"/>
        <source>day of month :</source>
        <translation>День месяца:</translation>
    </message>
    <message>
        <location line="+25"/>
        <source>1</source>
        <translation>1</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>2</source>
        <translation>2</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>3</source>
        <translation>3</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>4</source>
        <translation>4</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>5</source>
        <translation>5</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>6</source>
        <translation>6</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>7</source>
        <translation>7</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>8</source>
        <translation>8</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>9</source>
        <translation>9</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>10</source>
        <translation>10</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>11</source>
        <translation>11</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>12</source>
        <translation>12</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>13</source>
        <translation>13</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>14</source>
        <translation>14</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>15</source>
        <translation>15</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>16</source>
        <translation>16</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>17</source>
        <translation>17</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>18</source>
        <translation>18</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>19</source>
        <translation>19</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>20</source>
        <translation>20</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>21</source>
        <translation>21</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>22</source>
        <translation>22</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>23</source>
        <translation>23</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>24</source>
        <translation>24</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>25</source>
        <translation>25</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>26</source>
        <translation>26</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>27</source>
        <translation>27</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>28</source>
        <translation>28</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>29</source>
        <translation>29</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>30</source>
        <translation>30</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>31</source>
        <translation>31</translation>
    </message>
    <message>
        <location line="-491"/>
        <source>Check this if your machine does not support a graphical environment (eg server)</source>
        <translation>Установите флажок, если ваш компьютер не поддерживает графическую среду (например, сервер)</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Console Mode</source>
        <translation>Консольный режим</translation>
    </message>
    <message>
        <location line="+522"/>
        <source>okay</source>
        <translation>OK</translation>
    </message>
    <message>
        <location line="+20"/>
        <source>Cancel</source>
        <translation>Отмена</translation>
    </message>
    <message>
        <location line="+25"/>
        <source>schedule the execution of profiles as declared in the list above</source>
        <translation>Добавить в файл crontab расписание выполнения профилей</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>cronIT !!</source>
        <translation>Добавить в crontab</translation>
    </message>
    <message>
        <location filename="../src/scheduleDialog.cpp" line="-657"/>
        <location line="+78"/>
        <source>The existent schedule file is not a valid luckyBackup v.</source>
        <comment>v is for version</comment>
        <translation>Существующий файл расписания не совместим с файлом luckyBackup версии </translation>
    </message>
    <message>
        <location line="-77"/>
        <location line="+78"/>
        <source> file</source>
        <comment>BEWARE of the whitespace before file</comment>
        <translation> </translation>
    </message>
    <message>
        <location line="+78"/>
        <source>You have made changes without clicking the cronIT button</source>
        <translation>Расписание содержит несохранённые изменения</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Are you sure you want to close the schedule dialog ?</source>
        <translation>Вы уверены что хотите закрыть окно?</translation>
    </message>
    <message>
        <location line="+34"/>
        <source>Your crontab is updated successfully</source>
        <translation>Файл crontab успешно обновлён</translation>
    </message>
    <message>
        <location line="+100"/>
        <source>no crontab entries exist</source>
        <translation>в файле crontab нет записей</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>crontab content</source>
        <translation>содержимое файла crontab</translation>
    </message>
    <message>
        <location line="+156"/>
        <source>once, at system startup</source>
        <comment>full phrase: Execute profile xxxxx, once at system startup</comment>
        <translation>один раз при загрузке</translation>
    </message>
    <message>
        <location filename="../ui/scheduleDialog.ui" line="-463"/>
        <source>Run once, at startup</source>
        <translation>Выполнить один раз, при загрузке</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>@ reboot</source>
        <translation>после перезагрузки</translation>
    </message>
    <message>
        <location line="+480"/>
        <source>close this dialog</source>
        <translation>Закрыть окно</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>close</source>
        <translation>Закрыть</translation>
    </message>
    <message>
        <location line="+20"/>
        <source>Display the current crontab</source>
        <translation>Показать содержимое файла crontab</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>view current crontab</source>
        <translation>Файл crontab</translation>
    </message>
</context>
<context>
    <name>textDialog</name>
    <message>
        <location filename="../src/textDialog.cpp" line="+52"/>
        <source>Enter the name of the new profile :</source>
        <translation>Введите название нового профиля:</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>Enter the new name of the profile :</source>
        <translation>Введите новое название профиля:</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Profile description :</source>
        <translation>Описание профиля:</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>A profile with the same name already exists</source>
        <translation>Профиль с таким названием уже существует</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Please enter a different name</source>
        <translation>Пожалуйста, введите другое название</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Enter pasword :</source>
        <translation>Введите пароль:</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>Enter passphrase :</source>
        <translation>Введите парольную фразу:</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Do not show this again for this task</source>
        <translation>Больше не показывать это сообщение для этой задачи</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>You have selected to &quot;Backup the contents of the source directory&quot;&lt;br&gt;together with the &quot;delete files on the destination&quot; option</source>
        <translation>Вы выбрали тип &quot;Резервная копия каталога Источника внутри Назначения&quot;&lt;br&gt;одновременно с опцией &quot;Удалять файлы, которых нет в Источнике&quot;</translation>
    </message>
    <message>
        <location line="+0"/>
        <source>BEWARE, if your intention is NOT to clone source to destination !!</source>
        <translation>ОСТОРОЖНО, если вы НЕ намерены создавать точную копию Источника и Назначения !!</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Are you sure you wish to proceed ??</source>
        <translation>Вы уверены, что хотите продолжить?</translation>
    </message>
    <message>
        <location filename="../ui/textDialog.ui" line="+17"/>
        <source>luckyBackup</source>
        <translation>luckyBackup</translation>
    </message>
    <message>
        <location line="+81"/>
        <source>Okay</source>
        <translation>OK</translation>
    </message>
    <message>
        <location line="+27"/>
        <source>Cancel</source>
        <translation>Отмена</translation>
    </message>
    <message>
        <location filename="../src/textDialog.cpp" line="+8"/>
        <source>Copy command to clipboard</source>
        <translation>Копировать команду в буфер обмена</translation>
    </message>
    <message>
        <location line="+17"/>
        <source>eMail information</source>
        <translation>Результат выполнения команды</translation>
    </message>
    <message>
        <location line="+44"/>
        <source>No</source>
        <translation>Нет</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Yes</source>
        <translation>Да</translation>
    </message>
</context>
<context>
    <name>winDialog</name>
    <message>
        <location filename="../ui/winDialog.ui" line="+17"/>
        <source>luckyBackup</source>
        <translation>luckyBackup</translation>
    </message>
    <message>
        <location line="+18"/>
        <source>declaration of paths</source>
        <translation>Пути к программам</translation>
    </message>
    <message>
        <location line="+30"/>
        <source>rsync:</source>
        <translation>rsync:</translation>
    </message>
    <message>
        <location line="+19"/>
        <source>Enter the full path of the rsync command</source>
        <translation>Введите полный путь к исполняемому файлу rsync</translation>
    </message>
    <message>
        <location line="+10"/>
        <location line="+64"/>
        <location line="+64"/>
        <location line="+64"/>
        <location line="+64"/>
        <location line="+64"/>
        <location line="+64"/>
        <source>browse locally</source>
        <translation>Выбор файла на диске</translation>
    </message>
    <message>
        <location line="-367"/>
        <location line="+64"/>
        <location line="+64"/>
        <location line="+64"/>
        <location line="+64"/>
        <location line="+64"/>
        <location line="+64"/>
        <source>Use default value</source>
        <translation>По-умолчанию</translation>
    </message>
    <message>
        <location line="-366"/>
        <source>ssh:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+19"/>
        <source>Enter the full path of the ssh command</source>
        <translation>Введите полный путь к исполняемому файлу ssh</translation>
    </message>
    <message>
        <location line="+45"/>
        <source>cygpath:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+19"/>
        <source>Enter the full path of the cygpath command</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+45"/>
        <source>dosdev:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+19"/>
        <source>Enter the full path of the dosdev command</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+45"/>
        <source>main dir:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+19"/>
        <source>Enter the full path of the luckybackup directory</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+45"/>
        <source>vshadow dir:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+19"/>
        <source>Enter the full path of the vshadow directory</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+45"/>
        <source>temp dir:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+19"/>
        <source>Enter the full path of the temporary directory</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+58"/>
        <source>Okay</source>
        <translation>OK</translation>
    </message>
    <message>
        <location line="+27"/>
        <source>Cancel</source>
        <translation>Отмена</translation>
    </message>
    <message>
        <location filename="../src/winDialog.cpp" line="+147"/>
        <source>Select rsync command</source>
        <comment>file selection dialog title</comment>
        <translation>Укажите путь для запуска rsync</translation>
    </message>
    <message>
        <location line="+1"/>
        <location line="+6"/>
        <location line="+6"/>
        <location line="+6"/>
        <source>Executable Files (*.exe)</source>
        <translation>Исполняемые файлы (*.exe)</translation>
    </message>
    <message>
        <location line="-13"/>
        <source>Select ssh command</source>
        <comment>file selection dialog title</comment>
        <translation>Укажите путь для запуска ssh</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Select cygpath command</source>
        <comment>file selection dialog title</comment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location line="+6"/>
        <source>Select dosdev command</source>
        <comment>file selection dialog title</comment>
        <translation type="unfinished"/>
    </message>
</context>
</TS>