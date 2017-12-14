<?xml version="1.0" encoding="utf-8" ?>
<GSPModel GSPModelNode="True" DataFormatVersion="2.5.12" BizVersion="" xmlns:a="attribute" xmlns:c="collection" xmlns:o="object">
    <a:Version>2.5.12</a:Version>
    <a:Name>GSPModel</a:Name>
    <a:Mode>2</a:Mode>
    <c:Databases>
        <o:Database>
            <a:Name>DB</a:Name>
            <c:Tables>
                <o:Table TableKind="0">
                    <o:TableSchema>
                        <a:Name>Test</a:Name>
                        <a:CommandEnable>True</a:CommandEnable>
                        <a:ApplyUpdateEnabled>False</a:ApplyUpdateEnabled>
                        <a:PrimaryKeyMinVal>1</a:PrimaryKeyMinVal>
                        <c:FieldSchemas>
                            <o:FieldSchema FieldKind="0">
                                <a:FieldName>TestID</a:FieldName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>Name</a:FieldName>
                                <a:DataType>10</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="1">
                                <a:FieldName>TestPID</a:FieldName>
                                <a:DataType>2</a:DataType>
                                <a:MasterTableName>Test</a:MasterTableName>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>home</a:FieldName>
                                <a:DataType>10</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>A</a:FieldName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                            </o:FieldSchema>
                        </c:FieldSchemas>
                    </o:TableSchema>
                    <o:TableData>
                        <c:Records Format="1">
                            <o:Record>1,&apos;aaa&apos;,,,</o:Record>
                            <o:Record>2,&apos;bbb&apos;,,,</o:Record>
                            <o:Record>3,&apos;ccc&apos;,,,</o:Record>
                            <o:Record>4,&apos;a&apos;,1,,</o:Record>
                        </c:Records>
                    </o:TableData>
                </o:Table>
                <o:Table TableKind="0">
                    <o:TableSchema>
                        <a:Name>Child</a:Name>
                        <a:CommandEnable>True</a:CommandEnable>
                        <a:ApplyUpdateEnabled>False</a:ApplyUpdateEnabled>
                        <a:PrimaryKeyMinVal>1</a:PrimaryKeyMinVal>
                        <c:FieldSchemas>
                            <o:FieldSchema FieldKind="0">
                                <a:FieldName>ChildID</a:FieldName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>Name</a:FieldName>
                                <a:DataType>10</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>TestID</a:FieldName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="6">
                                <a:FieldName>Expr</a:FieldName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:NullExpr>1.3</a:NullExpr>
                            </o:FieldSchema>
                        </c:FieldSchemas>
                    </o:TableSchema>
                    <o:TableData>
                        <c:Records Format="1">
                            <o:Record>1,&apos;aaa&apos;,,1:1.30</o:Record>
                            <o:Record>2,&apos;bbb&apos;,,1:1.30</o:Record>
                            <o:Record>3,&apos;ccc&apos;,,1:1.30</o:Record>
                        </c:Records>
                    </o:TableData>
                </o:Table>
                <o:Table TableKind="0">
                    <o:TableSchema>
                        <a:Name>aaa</a:Name>
                        <a:CommandEnable>True</a:CommandEnable>
                        <a:ApplyUpdateEnabled>False</a:ApplyUpdateEnabled>
                        <a:PrimaryKeyMinVal>1</a:PrimaryKeyMinVal>
                        <c:FieldSchemas>
                            <o:FieldSchema FieldKind="0">
                                <a:FieldName>aaaID</a:FieldName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="1">
                                <a:FieldName>ChildID</a:FieldName>
                                <a:DataType>2</a:DataType>
                                <a:MasterTableName>Child</a:MasterTableName>
                            </o:FieldSchema>
                        </c:FieldSchemas>
                    </o:TableSchema>
                    <o:TableData/>
                </o:Table>
            </c:Tables>
        </o:Database>
    </c:Databases>
</GSPModel>
